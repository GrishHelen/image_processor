#include "help.h"

std::string Help() {
    const std::string help =
        "HELP:\n\n"
        "This is a console application to edit photos with various filters.\n\n"
        "To use it, please, enter the parameters in the following way:\n"
        "{program name} {path to the input file} {path to the output file} [-{filter_1 name} [argument_1 for filter_1] "
        "[argument_2 for filter_1] ...] [-{filter_2 name} [argument_1 for filter_2] [argument_2 for filter_2] ...] "
        "...\n\n"
        "Available filters:\n"
        "Crop              -crop width height     Crops the image to the given size. The upper left part of the image "
        "is used.\n"
        "Grayscale         -gs                    Converts the image to grayscale\n"
        "Negative          -neg                   Converts the image to a negative\n"
        "Sharpening        -sharp                 Increases the sharpness of the image\n"
        "Edge Detection    -edge threshold        Highlights the borders of the image\n"
        "Gaussian Blur     -blur sigma            Applies Gaussian blur to the image with sigma parameter\n"
        "Anaglyph          -anaglyph              Makes the effect of using 3d-glasses\n"
        "MergeImages       -merge other_path      Merges two images together\n\n"
        // "One more filter is planned to be made\n\n"
        "Example of usage:\n"
        "./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5";
    return help;
}