#include "negative.h"

Negative::Negative() : LinearFilter() {
    Coefficients red = {.red = -1, .free = 1};
    Coefficients green = {.green = -1, .free = 1};
    Coefficients blue = {.blue = -1, .free = 1};
    coefficients_ = {red, green, blue};
}