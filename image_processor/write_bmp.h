//
// Created by Daria Fominykh on 15.03.2024.
//
#include "string"
#include "memory"
#include "image.h"

#ifndef CPP_HSE_WRITE_BMP_H
#define CPP_HSE_WRITE_BMP_H



class WriteBmp {
private:
    std::shared_ptr<Image> image_;
    std::string output_file_path_;

public:
    WriteBmp(std::shared_ptr<Image> image, std::string output_file_path);

    void writeBMP();


};

#endif  // CPP_HSE_WRITE_BMP_H
