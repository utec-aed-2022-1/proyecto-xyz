#include "blockchain.hpp"

#include <utility>

#include "json.hpp"

using json = nlohmann::json;
using TDATA = std::string;

void to_json(json& j, Blockchain const& blocks) { j = json{blocks.bc}; }
void from_json(const json& j, Blockchain& blocks) { j.get_to(blocks.bc); }

auto blockchainFromFile(std::string const& filepath) -> Blockchain {
  std::ifstream fp{filepath};
  json j;
  fp >> j;
  return j.get<Blockchain>();
}

auto Blockchain::getBlocks() -> blocks_t const& { return this->bc; }

void Blockchain::push(TDATA data) {
  json j;
  j["data"] = data;
  this->push(j, 1);
}

void Blockchain::push(std::string filename, bool isfile) {
  if (!isfile) cout << "fichero que no es un fichero ingresado" << endl;
  // read json file
  filename = "blocksInput/" + filename;
  std::ifstream file(filename, std::ifstream::in);

  if (file.fail()) {
    // File does not exist code here
    cout << "This file does not exist" << endl;
    return;
  }

  // deserialize
  char c = file.get();
  std::string to_json;
  while (file.good()) {  // TODO: No funciona con el operador sobrecargado <<,
    // puede no ser la forma mas eficiente
    to_json += c;
    c = file.get();
  }
  json j = json::parse(to_json);

  this->push(j, 1);

  file.close();
}

void Blockchain::push(json data, size_t diferenciador) {
  cout << diferenciador << endl;
  Block blck(this->bc.size() + 1, data["data"]);
  if (!this->bc.empty())
    blck.prevHash = this->bc.back().hash;
  else
    this->valid_bc = true;
  blck.mineBlock(difficulty);
  this->bc.push_back(blck);
}

Block Blockchain::front() { return this->bc.front(); }

Block Blockchain::end() { return this->bc.back(); }

size_t Blockchain::size() { return this->bc.size(); }
bool Blockchain::empty() { return this->bc.empty(); }
size_t Blockchain::nextId() { return this->bc.size() + 1; }

TDATA Blockchain::find(size_t position) {
  if (position >= this->size()) {
    throw std::invalid_argument("find: index out of range");
  }

  return this->bc[position].data;
}

bool Blockchain::edit(size_t position, TDATA data) {
  if (position >= this->size()) {
    return false;
  }

  this->bc[position].data = data;
  for (size_t i = position; i < this->bc.size(); i++) {
    this->bc[position].nonce = nonceDefaultVal;
    this->bc[position].mineBlock(this->difficulty);
  }
  return true;
}

void Blockchain::clear() { this->bc.clear(); }
