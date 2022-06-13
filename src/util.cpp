#include "util.hpp"

#include <fstream>

#include "json.hpp"

using json = nlohmann::json;

void jsonToFile(std::string const& filepath, json const& j) {
  std::ofstream fp(filepath);
  fp << j;
}
