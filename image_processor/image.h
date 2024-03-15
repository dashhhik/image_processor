#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef CPP_HSE_IMAGE_H
#define CPP_HSE_IMAGE_H

#endif

struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct RGB {
    unsigned char blue, green, red;
};

class Image {
private:
    void ToGrayscale();
    void ToNegative();
    void ToGaussianBlur(int sigma);
    void Sharpening();

public:
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    std::vector<std::vector<RGB>> pixels;  // 2D vector for pixels
    void ApplyFilters(std::vector<std::pair<std::string, std::vector<std::string>>> filters);
};