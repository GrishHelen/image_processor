#include "matrix_filter.h"

class Sharpening : public MatrixFilter {
public:
    explicit Sharpening(double center_element = DefaultCenter);

    static constexpr double DefaultCenter = 5.0;
};