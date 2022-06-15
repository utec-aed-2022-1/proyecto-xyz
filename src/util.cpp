#include "util.hpp"

#include <filesystem>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;

void jsonToFile(std::string const& filepath, json const& j) {
  namespace fs = std::filesystem;
  fs::path p(filepath);
  fs::create_directories(p.parent_path());
  std::ofstream fp(filepath);
  assert(fp.is_open());
  fp << j;
}
