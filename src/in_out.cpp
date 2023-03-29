#include "in_out.h"

#include <fstream>

#pragma pack(push, 1)
struct BmpHeader {
    char id[2];
    uint32_t file_size;
    uint32_t unused;
    uint32_t offset;

    uint32_t header_size;
    int32_t image_width;
    int32_t image_height;

    uint16_t planes_count;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t horizontal_resolution = 0;
    int32_t vertical_resolution = 0;
    uint32_t colors_count = 0;
    uint32_t important_colors_count = 0;

    static const size_t OFFSET_SIZE = 54;
    static const size_t HEADER_SIZE = 40;
    static const uint16_t PLANES_COUNT = 1;
    static const uint16_t BITS_PER_PIXEL = 24;
    static const uint32_t COMPRESSION = 0;

    static const int32_t THREE = 3;
    static const int32_t FOUR = 4;
};
#pragma pack(pop)

bool CheckHeaderValidity(BmpHeader header) {
    if (header.offset != BmpHeader::OFFSET_SIZE) {
        std::cerr << "Invalid header size." << std::endl;
        return false;
    }
    if (header.image_width <= 0 || header.image_height <= 0) {
        std::cerr << "Invalid image size." << std::endl;
        return false;
    }
    if (header.planes_count != BmpHeader::PLANES_COUNT) {
        std::cerr << "Invalid number of planes." << std::endl;
        return false;
    }
    if (header.bits_per_pixel != BmpHeader::BITS_PER_PIXEL) {
        std::cerr << "Invalid number of bits per pixel." << std::endl;
        return false;
    }
    if (header.compression != BmpHeader::COMPRESSION) {
        std::cerr << "Invalid compression." << std::endl;
        return false;
    }
    return true;
}

Image LoadImage(const std::string input_path) {
    std::ifstream file(input_path, std::ios::binary);
    if (!file.is_open()) {
        throw std::logic_error("Failed to open file");
    }

    BmpHeader header;

    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (!CheckHeaderValidity(header)) {
        return Image();
    }
    int32_t width = header.image_width;
    int32_t height = header.image_height;

    Image image{static_cast<size_t>(height), static_cast<size_t>(std::abs(width))};
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            file.read(reinterpret_cast<char*>(&blue), 1);
            file.read(reinterpret_cast<char*>(&green), 1);
            file.read(reinterpret_cast<char*>(&red), 1);
            // std::cout << red << ' ' << green << ' ' << blue << std::endl;

            image.GetPixel(height - 1 - y, x) = {static_cast<double>(red) / RGB::BYTE_SIZE,
                                                 static_cast<double>(green) / RGB::BYTE_SIZE,
                                                 static_cast<double>(blue) / RGB::BYTE_SIZE};
        }
        file.ignore(((3 * width + 3) / 4) * 4 - 3 * width);
    }
    file.close();
    return image;
}

void SaveImage(const Image& image, const std::string output_path) {
    std::ofstream file(output_path, std::ios_base::binary);
    if (!file.is_open()) {
        throw std::logic_error("Failed to open file");
    }

    const uint32_t row_size = ((BmpHeader::BITS_PER_PIXEL * image.width_ + 3) / 4) * 4;
    const uint32_t trash_size = row_size * image.height_;

    BmpHeader header = {.id = {'B', 'M'},
                        .file_size = static_cast<uint32_t>(BmpHeader::OFFSET_SIZE + trash_size),
                        .offset = BmpHeader::OFFSET_SIZE,
                        .header_size = BmpHeader::HEADER_SIZE,
                        .image_width = static_cast<int32_t>(image.width_),
                        .image_height = static_cast<int32_t>(image.height_),
                        .planes_count = 1,
                        .bits_per_pixel = BmpHeader::BITS_PER_PIXEL,
                        .compression = BmpHeader::COMPRESSION};

    file.write(reinterpret_cast<const char*>(&header), sizeof(BmpHeader));

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            const RGB& pixel = image.At(image.height_ - 1 - i, j);
            uint8_t colors[3] = {static_cast<uint8_t>(pixel.blue * RGB::BYTE_SIZE),
                                 static_cast<uint8_t>(pixel.green * RGB::BYTE_SIZE),
                                 static_cast<uint8_t>(pixel.red * RGB::BYTE_SIZE)};
            file.write(reinterpret_cast<const char*>(&colors), sizeof(colors));
        }
        file.write("\0\0\0", static_cast<std::streamsize>(((3 * image.width_ + 3) / 4) * 4 - 3 * image.width_));
        file.flush();
    }
    file.close();
}