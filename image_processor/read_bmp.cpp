#include "read_bmp.h"
#include "errors.h"

void ReadBMP::ParseCommandLine(int argc, char** argv) {
    if (argc < 3) {
        throw ReadBMPError("Not enough arguments");
    }

    command_line_args_.inputFilePath = argv[1];
    command_line_args_.outputFilePath = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string_view filter = argv[i];
        std::vector<std::string> filter_args;

        //        TODO: Implement the following filters:

        if (filter == "gs" || filter == "sh" || filter == "gb") {
            if (i + 1 < argc) {
                filter_args.push_back(argv[i + 1]);
                i++;
            }
        }

        command_line_args_.filters.emplace_back(filter, filter_args);
    }
}

std::shared_ptr<Image> ReadBMP::GetImage(int argc, char** argv) {
    ParseCommandLine(argc, argv);
    ReadBmp();
    return image_;
}

void ReadBMP::ReadBmp() {
    const auto bm_hexadecimal = 0x4D42;

    std::ifstream file(command_line_args_.inputFilePath.data(), std::ios::binary);
    if (!file) {
        throw ReadBMPError("Unable to open file");
    }

    file.read(reinterpret_cast<char*>(&image_->fileHeader), sizeof(image_->fileHeader));
    file.read(reinterpret_cast<char*>(&image_->infoHeader), sizeof(image_->infoHeader));

    if (image_->fileHeader.bfType != bm_hexadecimal) {
        throw ReadBMPError("Not a BMP file");
    }

    file.seekg(image_->fileHeader.bfOffBits, std::ios::beg);

    const int padding = (4 - (image_->infoHeader.biWidth * 3) % 4) % 4;
    std::vector<char> row_data(image_->infoHeader.biWidth * 3 + padding);

    // Resize the 2D vector to fit the image dimensions
    image_->pixels.resize(image_->infoHeader.biHeight);

    for (int y = 0; y < image_->infoHeader.biHeight; ++y) {
        file.read(row_data.data(), static_cast<std::streamsize>(row_data.size()));

        // Prepare a row in the 2D vector
        image_->pixels[y].resize(image_->infoHeader.biWidth);

        for (int x = 0; x < image_->infoHeader.biWidth; ++x) {
            RGB pixel;
            pixel.blue = row_data[x * 3];
            pixel.green = row_data[x * 3 + 1];
            pixel.red = row_data[x * 3 + 2];

            // Assign the pixel to the correct position in the 2D vector
            image_->pixels[y][x] = pixel;
        }
    }
}