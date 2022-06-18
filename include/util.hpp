#pragma once

#include "json.hpp"

// From: https://www.cppstories.com/2019/02/2lines3featuresoverload.html/
template <class... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

void jsonToFile(std::string const& filepath, nlohmann::json const& j);
