#pragma once

#include <vector>
#include <algorithm>

struct RGB {
    double red = 0;
    double green = 0;
    double blue = 0;

    RGB& operator+=(const RGB&);
    RGB operator*(double) const;
    static const int32_t BYTE_SIZE = 255;
};

class Image {
public:
    Image() = default;
    Image(const Image&);
    explicit Image(const std::vector<std::vector<RGB>>&);
    Image(size_t, size_t);

    RGB& GetPixel(size_t, size_t);
    RGB At(size_t, size_t) const;

    static RGB MergeRGB(RGB, RGB);
    static RGB MakeValidRGB(RGB&);

    void SetRow(int32_t, const std::vector<RGB>&);
    const std::vector<RGB>& GetRow(int32_t) const;
    void Resize(size_t, size_t);

    size_t height_;
    size_t width_;

private:
    std::vector<std::vector<RGB>> pixels_;
};
