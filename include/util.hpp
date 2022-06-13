#pragma once

#include "json.hpp"

void jsonToFile(std::string const& filepath, nlohmann::json const& j);
