#include "linear_filter.h"

class Grayscale : public LinearFilter {
public:
    Grayscale();

    static constexpr double DefaultRed = 0.299;
    static constexpr double DefaultGreen = 0.587;
    static constexpr double DefaultBlue = 0.114;
};