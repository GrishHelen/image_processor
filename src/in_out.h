#pragma once

#include "image.h"

#include <iostream>

Image LoadImage(const std::string);
void SaveImage(const Image&, const std::string);
