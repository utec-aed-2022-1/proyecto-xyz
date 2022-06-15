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
  Block new_block;

  new_block.data = std::move(data);
  new_block.id = this->nextId();

  if (!this->empty()) {
    new_block.prevHash = bc.back().hash;
  }

  new_block.mine(this->difficulty);
  this->bc.push_back(new_block);
}

bool Blockchain::isValid() {
  if (this->size() == 0) {
    return true;
  }

  auto it = this->bc.begin();
  std::string const* prevHash = &it->hash;

  if (!it->isValid(this->difficulty)) {
    return false;
  }
  ++it;

  while (it != this->bc.end()) {
    if (it->prevHash != *prevHash || it->calculateHash() != it->hash ||
        !it->isValid(this->difficulty)) {
      return false;
    }

    prevHash = &it->hash;
  }

  return true;
}

void Blockchain::makeValid() {
  if (this->empty()) {
    return;
  }

  auto it = this->bc.begin();
  it->mine(this->difficulty);
  std::string const* prevHash = &it->hash;

  while (it != this->bc.end()) {
    it->prevHash = *prevHash;
    it->mine(this->difficulty);

    prevHash = &it->hash;
  }
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
