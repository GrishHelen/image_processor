#pragma once

#include "parser.h"
#include "filters/filter.h"
#include "filters/crop/crop.h"
#include "filters/linear_filters/grayscale.h"
#include "filters/linear_filters/negative.h"
#include "filters/matrix_filters/matrix_filter.h"
#include "filters/matrix_filters/sharp.h"
#include "filters/matrix_filters/edge_detection.h"
#include "filters/gaussian_blur/gaussian_blur.h"
#include "filters/anaglyph/anaglyph.h"
#include "filters/merge_images/merge_images.h"

#include <vector>
#include <memory>

class Controller {
public:
    static std::vector<std::shared_ptr<Filter>> CreateFilters(std::vector<FilterConfig>&);
    static Image ApplyFilters(Image image, const std::vector<std::shared_ptr<Filter>>&);
};