#include "controller.h"
#include "in_out.h"

#include <iostream>

std::vector<std::shared_ptr<Filter>> Controller::CreateFilters(std::vector<FilterConfig>& filter_configs) {
    std::vector<std::shared_ptr<Filter>> filters;

    for (const auto& config : filter_configs) {
        if (config.name == "crop") {

            if (config.args.size() != 2) {
                throw std::logic_error("Invalid amount arguments for crop");
            }

            try {
                size_t width = std::stoull(config.args[0]);
                size_t height = std::stoull(config.args[1]);

                if (std::stod(config.args[0]) != static_cast<double>(width) ||
                    std::stod(config.args[1]) != static_cast<double>(height)) {
                    throw std::logic_error("Invalid argument for crop");
                }

                filters.push_back(std::make_shared<Crop>(height, width));
            } catch (std::invalid_argument& exception) {
                throw std::logic_error("Invalid argument for crop");
            }

        } else if (config.name == "gs") {

            if (!config.args.empty()) {
                throw std::logic_error("Invalid amount arguments for grayscale");
            }

            filters.push_back(std::make_shared<Grayscale>());

        } else if (config.name == "neg") {

            if (!config.args.empty()) {
                throw std::logic_error("Invalid amount arguments for negative");
            }
            filters.push_back(std::make_shared<Negative>());

        } else if (config.name == "sharp") {

            if (!config.args.empty()) {
                throw std::logic_error("Invalid amount arguments for sharpening");
            }
            filters.push_back(std::make_shared<Sharpening>());

        } else if (config.name == "edge") {

            if (config.args.size() != 1) {
                throw std::logic_error("Invalid amount arguments for edge");
            }

            try {
                double threshold = std::stod(config.args[0]);
                filters.push_back(std::make_shared<EdgeDetection>(threshold));
            } catch (std::invalid_argument& exception) {
                throw std::logic_error("Invalid argument for edge");
            }

        } else if (config.name == "blur") {

            if (config.args.size() != 1) {
                throw std::logic_error("Invalid amount arguments for blur");
            }

            try {
                double sigma = std::stod(config.args[0]);
                filters.push_back(std::make_shared<GaussianBlur>(sigma));
            } catch (std::invalid_argument& exception) {
                throw std::logic_error("Invalid argument for blur");
            }

        } else if (config.name == "anaglyph") {

            if (!config.args.empty()) {
                throw std::logic_error("Invalid amount arguments for anaglyph");
            }
            filters.push_back(std::make_shared<Anaglyph>());

        } else if (config.name == "merge") {

            if (config.args.size() != 1) {
                throw std::logic_error("Invalid amount arguments for merge");
            }

            try {
                Image other_image = LoadImage(config.args[0]);
                filters.push_back(std::make_shared<MergeImages>(other_image));
            } catch (std::invalid_argument& exception) {
                throw std::logic_error("Invalid argument for merge");
            }

        } else {
            throw std::logic_error("No filter named " + config.name);
        }
    }

    return filters;
}

Image Controller::ApplyFilters(Image image, const std::vector<std::shared_ptr<Filter>>& filters) {
    for (const auto& filter : filters) {
        image = filter->Apply(image);
    }
    return image;
}