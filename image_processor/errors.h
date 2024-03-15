#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef CPP_HSE_READ_BMP_ERROR_H
#define CPP_HSE_READ_BMP_ERROR_H

class ReadBMPError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class WriteBMPError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

#endif  // CPP_HSE_READ_BMP_ERROR_H
