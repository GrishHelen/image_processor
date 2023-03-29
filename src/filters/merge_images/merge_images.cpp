#include "merge_images.h"

MergeImages::MergeImages(Image& other_image) : Filter(), other_image_(other_image) {
}

Image MergeImages::Apply(const Image& image) {
    size_t width = std::min(image.width_, other_image_.width_);
    size_t height = std::min(image.height_, other_image_.height_);

    Image result_image = Image(height, width);
    for (size_t row = 0; row < height; ++row) {
        for (size_t column = 0; column < width; ++column) {
            result_image.GetPixel(row, column) = Image::MergeRGB(image.At(row, column), other_image_.At(row, column));
        }
    }
    return result_image;
}