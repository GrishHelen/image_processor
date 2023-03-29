#include "crop.h"

Crop::Crop(size_t height, size_t width) : Filter(), height_(height), width_(width) {
}

Image Crop::Apply(const Image& image) {
    Image result_image = Image(image);
    result_image.Resize(height_, width_);
    return result_image;
}