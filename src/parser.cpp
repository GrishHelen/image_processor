#include "parser.h"

#include <iostream>
#include <tuple>

bool FilterConfig::operator==(const FilterConfig& other) const {
    return std::tie(name, args) == std::tie(other.name, other.args);
}

bool operator==(const ParserResults& first, const ParserResults& second) {
    if (first.input_path != second.input_path || first.output_path != second.output_path ||
        first.filters.size() != second.filters.size()) {
        return false;
    }
    size_t filters_count = first.filters.size();
    for (size_t i = 0; i < filters_count; ++i) {
        if (first.filters[i] != second.filters[i]) {
            return false;
        }
    }
    return true;
}

ParserResults ParseArgs(int32_t argc, const char* argv[]) {
    ParserResults parser_results;
    if (argc < 3) {
        std::cerr << Help() << std::endl;
        throw std::logic_error("Need more arguments");
    }

    parser_results.input_path = argv[1];
    parser_results.output_path = argv[2];

    FilterConfig filter;

    for (int32_t index = 3; index < argc; ++index) {
        if (argv[index][0] == '-') {
            if (filter != FilterConfig()) {
                parser_results.filters.push_back(filter);
            }
            filter.args.clear();
            filter.name = static_cast<std::string>(argv[index]).substr(1);
        } else {
            if (index == 3) {
                throw std::logic_error("Invalid arguments");
            }
            filter.args.push_back(static_cast<std::string>(argv[index]));
        }
    }
    if (filter != FilterConfig()) {
        parser_results.filters.push_back(filter);
    }
    return parser_results;
}