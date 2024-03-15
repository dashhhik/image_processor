#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"

#ifndef CPP_HSE_READ_BMP_H
#define CPP_HSE_READ_BMP_H

struct CommandLineArgs {
    std::string inputFilePath;
    std::string outputFilePath;
    std::vector<std::pair<std::string, std::vector<std::string>>> filters;
};

class ReadBMP {
public:
    std::shared_ptr<Image> GetImage(int argc, char** argv);
    CommandLineArgs command_line_args_;

private:
    std::shared_ptr<Image> image_;

    void ReadBmp();
    void ParseCommandLine(int argc, char** argv);
};

#endif  // CPP_HSE_READ_BMP_H
