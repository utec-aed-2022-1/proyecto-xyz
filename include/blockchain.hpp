#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "block.hpp"
#include "json.hpp"
#include "vector.hpp"

template <typename T>
class Blockchain {
 public:
  using block_t = Block<T>;
  using blocks_t = Vector<block_t>;

  using iterator = typename blocks_t::iterator;

 private:
  friend void to_json(nlohmann::json& j, Blockchain const& blocks) {
    j = json{blocks.bc};
  }
  friend void from_json(const nlohmann::json& j, Blockchain& blocks) {
    j.get_to(blocks.bc);
  }

  using json = nlohmann::json;

  blocks_t bc;
  uint32_t difficulty = 3;

 public:
  Blockchain() = default;

  Blockchain(Blockchain const& other) = default;
  Blockchain(Blockchain&& other) noexcept = default;

  auto operator=(Blockchain const& other) -> Blockchain& = default;
  auto operator=(Blockchain&& other) noexcept -> Blockchain& = default;

  auto getBlocks() -> blocks_t const& { return this->bc; }

  auto push(T data) -> block_t const& {
    block_t new_block;

    new_block.data = std::move(data);
    new_block.id = this->nextId();

    if (!this->empty()) {
      new_block.prevHash = bc.back().hash;
    }

    new_block.mine(this->difficulty);
    this->bc.push_back(new_block);

    return this->bc.back();
  }

  auto isValid() -> bool {
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

  void makeValid() {
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

  auto begin() -> iterator { return this->bc.begin(); }
  auto end() -> iterator { return this->bc.end(); }

  auto front() -> block_t { return this->bc.front(); }
  auto back() -> block_t { return this->bc.back(); }

  [[nodiscard]] auto size() const -> size_t { return this->bc.size(); }
  auto empty() -> bool { return this->bc.empty(); }

  auto nextId() -> size_t { return this->bc.size() + 1; };

  auto find(size_t position) -> T const& { return this->bc.at(position).data; }

  auto at(size_t index) -> block_t const& { return this->bc.at(index); }

  void edit(size_t position, T data) {
    block_t& blk = this->bc.at(position);
    blk.data = std::move(data);
    blk.mine(this->difficulty);

    std::string const* prevHash = &blk.hash;

    for (size_t i = position + 1; i < this->bc.size(); ++i) {
      block_t& blk = this->bc[i];

      blk.prevHash = *prevHash;
      blk.mine(this->difficulty);

      prevHash = &blk.hash;
    }
  }

  void clear() { this->bc.clear(); }

  ~Blockchain() = default;
};

template <typename T>
auto blockchainFromFile(std::string const& filepath) -> Blockchain<T> {
  std::ifstream fp{filepath};
  nlohmann::json j;
  fp >> j;
  return j.get<Blockchain<T>>();
}
