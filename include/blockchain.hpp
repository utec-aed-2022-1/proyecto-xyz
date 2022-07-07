#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "block.hpp"
#include "json.hpp"

class Blockchain {
 public:
  using blocks_t = std::vector<Block>;

 private:
  friend void to_json(nlohmann::json& j, Blockchain const& blocks);
  friend void from_json(const nlohmann::json& j, Blockchain& blocks);

  using TDATA = std::string;
  using THASH = std::string;
  using json = nlohmann::json;

  blocks_t bc;
  uint32_t difficulty = 3;

 public:
  Blockchain() = default;

  Blockchain(Blockchain const& other) = default;
  Blockchain(Blockchain&& other) noexcept = default;

  auto operator=(Blockchain const& other) -> Blockchain& = default;
  auto operator=(Blockchain&& other) noexcept -> Blockchain& = default;

  auto getBlocks() -> blocks_t const&;

  void push(TDATA data);
  auto isValid() -> bool;
  void makeValid();

  auto front() -> Block<T>;
  auto end() -> Block<T>;

  auto size() -> size_t;
  auto empty() -> bool;
  auto nextId() -> size_t;

  auto find(size_t position) -> TDATA const&;
  void edit(size_t position, TDATA data);
  void clear();

  ~Blockchain() = default;
};

void to_json(nlohmann::json& j, Blockchain const& blocks);
void from_json(const nlohmann::json& j, Blockchain& blocks);

auto blockchainFromFile(std::string const& filepath) -> Blockchain;
