#pragma once

#include "../filter.h"
#include <vector>

struct Coefficients {
    double red = 0;
    double green = 0;
    double blue = 0;
    double free = 0;
};

class LinearFilter : public Filter {
public:
    LinearFilter();
    Image Apply(const Image&) override;
    RGB ProduceNewColor(RGB) const;

protected:
    std::vector<Coefficients> coefficients_;
};