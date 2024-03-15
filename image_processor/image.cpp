#include "image.h"

void Image::ToGrayscale() {
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            unsigned char intensity =
                static_cast<unsigned char>(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);
            pixel.red = pixel.green = pixel.blue = intensity;
        }
    }
}

void Image::ToNegative() {
    for (auto& row : pixels) {
        for (auto& pixel : row) {
            pixel.red = 1 - pixel.red;
            pixel.blue = 1 - pixel.blue;
            pixel.green = 1 - pixel.green;
        }
    }
}

void Image::Sharpening() {

    constexpr float Kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    auto original_pixels = pixels;

    for (int y = 0; y < infoHeader.biHeight; ++y) {
        for (int x = 0; x < infoHeader.biWidth; ++x) {
            float new_red = 0;
            float new_green = 0;
            float new_blue = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {

                    int px = std::min(std::max(x + kx, 0), infoHeader.biWidth - 1);
                    int py = std::min(std::max(y + ky, 0), infoHeader.biHeight - 1);

                    new_red += Kernel[ky + 1][kx + 1] * static_cast<float>(original_pixels[py][px].red) / 255.0f;
                    new_green += Kernel[ky + 1][kx + 1] * static_cast<float>(original_pixels[py][px].green) / 255.0f;
                    new_blue += Kernel[ky + 1][kx + 1] * static_cast<float>(original_pixels[py][px].blue) / 255.0f;
                }
            }

            auto clamp = [](int val, int min_val, int max_val) -> int {
                return std::min(std::max(val, min_val), max_val);
            };

            pixels[y][x].red = clamp(new_red, 0, 255);
            pixels[y][x].green = clamp(new_green, 0, 255);
            pixels[y][x].blue = clamp(new_blue, 0, 255);
        }
    }
}

void Image::ApplyFilters(std::vector<std::pair<std::string, std::vector<std::string>>> filters) {
    for (const auto& filter : filters) {
        const auto& filter_name = filter.first;
        const auto& params = filter.second;

        //      TODO: Implement the following filters:
        //        TODO: use map instead of if-else
        if (filter_name == "sh") {
            Sharpening();
        } else if (filter_name == "gb") {
            ToGaussianBlur(std::stoi(params[0]));
        } else if (filter_name == "ng") {
            ToNegative();
        } else {
            ToGrayscale();
        }
    }
}
