#pragma once

#include "help.h"

#include <string>
#include <vector>

struct FilterConfig {
    std::string name;
    std::vector<std::string> args;

    bool operator==(const FilterConfig&) const;
};

struct ParserResults {
    std::string input_path;
    std::string output_path;
    std::vector<FilterConfig> filters;

    friend bool operator==(const ParserResults&, const ParserResults&);
};

ParserResults ParseArgs(int argc, const char* argv[]);