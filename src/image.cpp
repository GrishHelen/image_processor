#include "image.h"

#include <cmath>

Image::Image(const Image& image) : height_(image.height_), width_(image.width_), pixels_(image.pixels_) {
}

Image::Image(const std::vector<std::vector<RGB>>& pixels) : height_(pixels.size()), pixels_(pixels) {
    if (height_ != 0) {
        width_ = pixels[0].size();
    }
}

Image::Image(size_t height, size_t width) : height_(height), width_(width) {
    pixels_.resize(height_, std::vector<RGB>(width_, RGB()));
}

RGB& RGB::operator+=(const RGB& other) {
    this->red += other.red;
    this->green += other.green;
    this->blue += other.blue;
    return *this;
}

RGB RGB::operator*(double coefficient) const {
    return {this->red * coefficient, this->green * coefficient, this->blue * coefficient};
}

RGB& Image::GetPixel(size_t row, size_t column) {
    return pixels_[row][column];
}

RGB Image::At(size_t row, size_t column) const {
    if (row < 0) {
        row = 0;
    } else if (row >= height_) {
        row = height_ - 1;
    }
    if (column < 0) {
        column = 0;
    } else if (column >= width_) {
        column = width_ - 1;
    }
    return pixels_[row][column];
}

RGB Image::MergeRGB(RGB first, RGB second) {
    RGB new_color = {.red = (first.red + second.red) / 2,
                     .green = (first.green + second.green) / 2,
                     .blue = (first.blue + second.blue) / 2};
    return MakeValidRGB(new_color);
}

RGB Image::MakeValidRGB(RGB& color) {
    return {std::clamp(color.red, 0.0, 1.0), std::clamp(color.green, 0.0, 1.0), std::clamp(color.blue, 0.0, 1.0)};
}

void Image::SetRow(int32_t row_index, const std::vector<RGB>& new_row) {
    pixels_[row_index] = new_row;
}

const std::vector<RGB>& Image::GetRow(int32_t row_index) const {
    return pixels_[row_index];
}
void Image::Resize(size_t height, size_t width) {
    height_ = height;
    width_ = width;
    pixels_.resize(height_);
    for (auto& row : pixels_) {
        row.resize(width_);
    }
}
