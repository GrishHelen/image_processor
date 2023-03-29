#include "gaussian_blur.h"

#include <cmath>
#include <numbers>

GaussianBlur::GaussianBlur(double sigma) : sigma_(sigma) {
    radius_to_apply_ = std::ceil(sigma_ * 3);
    coefficients_.resize(radius_to_apply_ + 1);
    double help_coefficient = std::sqrt(2 * std::numbers::pi) * sigma_;
    for (int32_t i = 0; i <= radius_to_apply_; ++i) {
        coefficients_[i] = 1 / (help_coefficient * std::exp(i * i / (2 * sigma_ * sigma_)));
    }
}

Image GaussianBlur::Apply(const Image& image) {
    Image help_image = Image(image.height_, image.width_);
    size_t current_column = 0;
    for (size_t column = 0; column < image.width_; ++column) {
        for (size_t row = 0; row < image.height_; ++row) {

            RGB& pixel_to_change = help_image.GetPixel(row, column);
            for (int32_t d_column = -radius_to_apply_; d_column <= radius_to_apply_; ++d_column) {
                d_column + static_cast<int32_t>(column) < 0
                    ? current_column = 0
                    : current_column = std::min(d_column + column, image.width_ - 1);
                pixel_to_change += image.At(row, current_column) * coefficients_[std::abs(d_column)];
            }
        }
    }

    Image result_image = Image(help_image.height_, help_image.width_);
    size_t current_row = 0;
    for (size_t column = 0; column < help_image.width_; ++column) {
        for (size_t row = 0; row < help_image.height_; ++row) {

            RGB& pixel_to_change = result_image.GetPixel(row, column);
            for (int32_t d_row = -radius_to_apply_; d_row <= radius_to_apply_; ++d_row) {
                d_row + static_cast<int32_t>(row) < 0 ? current_row = 0
                                                      : std::min(current_row = d_row + row, help_image.height_ - 1);
                pixel_to_change += help_image.At(current_row, column) * coefficients_[std::abs(d_row)];
            }

            pixel_to_change = Image::MakeValidRGB(pixel_to_change);
        }
    }

    return result_image;
}