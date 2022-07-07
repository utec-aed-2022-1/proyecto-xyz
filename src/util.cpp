#include "util.hpp"

#include <filesystem>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;

void jsonToFile(std::string const& filepath, json const& j) {
  namespace fs = std::filesystem;
  fs::path p(filepath);

  if (auto p_path = p.parent_path(); p_path != "") {
    fs::create_directories(p_path);
  }

  std::ofstream fp(filepath);
  assert(fp.is_open());
  fp << j;
}
