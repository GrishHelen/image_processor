#include "in_out.h"
#include "controller.h"

int main(int argc, const char *argv[]) {
    std::cout << Help() << '\n';
    return 0;
    try {
        ParserResults parser_results = ParseArgs(argc, argv);
        Image original_image = LoadImage(parser_results.input_path);
        auto filters_to_apply = Controller::CreateFilters(parser_results.filters);
        Image result_image = Controller::ApplyFilters(original_image, filters_to_apply);
        SaveImage(result_image, parser_results.output_path);
    } catch (std::exception &exception) {
        std::cerr << "Something went wrong: " << exception.what() << "\n\n\n" << Help()
                  << std::endl;
    }
    return 0;
}