#include "sharp.h"

Sharpening::Sharpening(double center_element) : MatrixFilter() {
    matrix_ = {{0, -1, 0}, {-1, center_element, -1}, {0, -1, 0}};
}