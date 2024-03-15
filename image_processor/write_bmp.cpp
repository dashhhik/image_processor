//
// Created by Daria Fominykh on 15.03.2024.
//

#include "write_bmp.h"
#include "errors.h"

WriteBmp::WriteBmp(std::shared_ptr<Image> image, std::string output_file_path) {
    image_ = image;
    output_file_path_ = output_file_path;
}

void WriteBmp::writeBMP() {
    std::ofstream file(output_file_path_, std::ios::binary);
    if (!file) {
        throw WriteBMPError("Unable to open file");
    }

    file.write(reinterpret_cast<char*>(&image_->fileHeader), sizeof(image_->fileHeader));
    file.write(reinterpret_cast<char*>(&image_->infoHeader), sizeof(image_->infoHeader));

    const int padding = (4 - (image_->infoHeader.biWidth * 3) % 4) % 4;
    std::vector<char> row_data(image_->infoHeader.biWidth * 3 + padding);

    for (int y = 0; y < image_->infoHeader.biHeight; ++y) {
        file.write(row_data.data(), static_cast<std::streamsize>(row_data.size()));
    }
}