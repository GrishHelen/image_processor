#pragma once

#include "../filter.h"

#include <vector>

class MatrixFilter : public Filter {
public:
    MatrixFilter() : Filter() {
    }
    explicit MatrixFilter(std::vector<std::vector<double>>);
    static RGB HelpProduceColor(RGB, double);
    RGB ProduceNewColor(const Image&, int32_t, int32_t) const;
    Image Apply(const Image&) override;

protected:
    std::vector<std::vector<double>> matrix_;
};