#include "../filter.h"

class Anaglyph : public Filter {
public:
    Anaglyph() = default;
    Image Apply(const Image&) override;

private:
    static constexpr double SHIFT = 0.01;
};