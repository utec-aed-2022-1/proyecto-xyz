#pragma once

#include <fstream>

#include "json.hpp"

// From: https://www.cppstories.com/2019/02/2lines3featuresoverload.html/
template <class... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

template <typename T>
auto getTFromJsonFile(std::string const& filepath) -> T {
  std::ifstream fp{filepath};
  nlohmann::json j;
  fp >> j;
  return j.get<T>();
}

void jsonToFile(std::string const& filepath, nlohmann::json const& j);
