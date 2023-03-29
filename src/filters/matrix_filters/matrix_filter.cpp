#include "matrix_filter.h"

MatrixFilter::MatrixFilter(std::vector<std::vector<double>> matrix) : Filter(), matrix_(matrix) {
}

RGB MatrixFilter::HelpProduceColor(RGB color, double coefficient) {
    return {color.red * coefficient, color.green * coefficient, color.blue * coefficient};
}

RGB MatrixFilter::ProduceNewColor(const Image& image, int32_t row, int32_t column) const {
    RGB new_color = {0, 0, 0};
    int32_t current_row = 0;
    int32_t current_column = 0;

    for (int32_t i = -1; i <= 1; ++i) {
        for (int32_t j = -1; j <= 1; ++j) {
            current_row = std::max(0, row + i);
            current_column = std::max(0, column + j);
            new_color += HelpProduceColor(image.At(current_row, current_column), matrix_[i + 1][j + 1]);
        }
    }
    return Image::MakeValidRGB(new_color);
}

Image MatrixFilter::Apply(const Image& image) {
    Image result_image = Image(image);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            result_image.GetPixel(i, j) = ProduceNewColor(image, static_cast<int32_t>(i), static_cast<int32_t>(j));
        }
    }

    return result_image;
}