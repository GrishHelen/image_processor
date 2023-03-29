#include "../filter.h"

class GaussianBlur : public Filter {
public:
    explicit GaussianBlur(double sigma);
    Image Apply(const Image&) override;

private:
    double sigma_;
    int32_t radius_to_apply_;
    std::vector<double> coefficients_;
};