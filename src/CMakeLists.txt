add_executable(
        image_processor
        image_processor.cpp
        parser.cpp
        in_out.cpp
        controller.cpp
        help.cpp
        image.cpp
        filters/crop/crop.cpp
        filters/linear_filters/linear_filter.cpp
        filters/linear_filters/grayscale.cpp
        filters/linear_filters/negative.cpp
        filters/matrix_filters/edge_detection.cpp
        filters/matrix_filters/matrix_filter.cpp
        filters/matrix_filters/sharp.cpp
        filters/gaussian_blur/gaussian_blur.cpp
        filters/anaglyph/anaglyph.cpp
        filters/merge_images/merge_images.cpp
)