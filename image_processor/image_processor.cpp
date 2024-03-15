#include "read_bmp.h"
#include "write_bmp.h"

int main(int argc, char** argv) {
    ReadBMP reader;
    auto image = reader.GetImage(argc, argv);
    image->ApplyFilters(reader.command_line_args_.filters);
    WriteBmp writer(image, reader.command_line_args_.outputFilePath);
    writer.writeBMP();
    return 0;
}
