#include "edge_detection.h"
#include "../linear_filters/grayscale.h"
#include "sharp.h"

EdgeDetection::EdgeDetection() : MatrixFilter() {
}

EdgeDetection::EdgeDetection(double threshold) : MatrixFilter(), threshold_(threshold) {
}

double EdgeDetection::AverageAmongColor(RGB& color) const {
    double average = (color.red + color.green + color.blue) / 3;
    return average;
}

Image EdgeDetection::Apply(const Image& image) {
    Image result_image = Grayscale().Apply(Image(image));
    result_image = Sharpening(4).Apply(result_image);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            RGB& color = result_image.GetPixel(i, j);
            if (AverageAmongColor(color) > threshold_) {
                color = {1, 1, 1};
            } else {
                color = {0, 0, 0};
            }
        }
    }

    return result_image;
}