#include "anaglyph.h"
#include "../linear_filters/grayscale.h"

#include <iostream>

Image Anaglyph::Apply(const Image& image) {
    int32_t image_shift = static_cast<int32_t>(std::max(1.0, static_cast<double>(image.width_) * SHIFT));
    Image help_image = Grayscale().Apply(Image(image));
    Image result_image = Image(help_image.height_, help_image.width_);
    RGB delete_red;
    RGB red;
    for (size_t row = 0; row < help_image.height_; ++row) {
        for (size_t column = 0; column < help_image.width_; ++column) {
            delete_red = help_image.At(
                row, static_cast<int32_t>(column) - image_shift < 0 ? 0 : static_cast<int32_t>(column) - image_shift);
            delete_red.red = 0;

            red = {.red = help_image.At(row, std::min(column + image_shift, help_image.width_ - 1)).red};

            result_image.GetPixel(row, column) = {.red = red.red, .green = delete_red.green, .blue = delete_red.blue};
        }
    }

    return result_image;
}