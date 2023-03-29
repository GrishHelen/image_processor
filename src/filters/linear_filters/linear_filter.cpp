#include "linear_filter.h"

LinearFilter::LinearFilter() : Filter() {
    Coefficients coefficients;
    coefficients_ = {coefficients, coefficients, coefficients};
}

RGB LinearFilter::ProduceNewColor(RGB color) const {
    RGB new_color;
    new_color.red = color.red * this->coefficients_[0].red + color.green * this->coefficients_[0].green +
                    color.blue * this->coefficients_[0].blue + this->coefficients_[0].free;
    new_color.green = color.red * this->coefficients_[1].red + color.green * this->coefficients_[1].green +
                      color.blue * this->coefficients_[1].blue + this->coefficients_[1].free;
    new_color.blue = color.red * this->coefficients_[2].red + color.green * this->coefficients_[2].green +
                     color.blue * this->coefficients_[2].blue + this->coefficients_[2].free;
    return Image::MakeValidRGB(new_color);
}

Image LinearFilter::Apply(const Image& image) {
    Image result_image = Image(image);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            result_image.GetPixel(i, j) = ProduceNewColor(image.At(i, j));
        }
    }

    return result_image;
}