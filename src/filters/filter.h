#pragma once

#include "../image.h"

class Filter {
public:
    Filter() = default;
    virtual Image Apply(const Image&) = 0;
    virtual ~Filter() = default;
};