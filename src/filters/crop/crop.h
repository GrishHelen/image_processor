#include "../filter.h"

#include <cstdlib>

class Crop : public Filter {
public:
    Crop(size_t height, size_t width);
    Image Apply(const Image&) override;

private:
    size_t height_;
    size_t width_;
};