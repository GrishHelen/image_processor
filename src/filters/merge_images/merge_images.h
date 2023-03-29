#include "../filter.h"

class MergeImages : public Filter {
public:
    explicit MergeImages(Image&);
    Image Apply(const Image&) override;

private:
    Image other_image_;
};