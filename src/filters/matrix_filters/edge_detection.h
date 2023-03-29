#include "matrix_filter.h"

class EdgeDetection : public MatrixFilter {
public:
    EdgeDetection();
    explicit EdgeDetection(double);
    Image Apply(const Image&) override;
    double AverageAmongColor(RGB&) const;

private:
    double threshold_;
};