#include "grayscale.h"

Grayscale::Grayscale() : LinearFilter() {
    Coefficients coefficients = {.red = DefaultRed, .green = DefaultGreen, .blue = DefaultBlue};
    coefficients_ = {coefficients, coefficients, coefficients};
}