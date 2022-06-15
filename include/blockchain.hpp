#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "block.hpp"
#include "json.hpp"

class Blockchain {
 private:
  friend void to_json(nlohmann::json& j, Blockchain const& blocks);
  friend void from_json(const nlohmann::json& j, Blockchain& blocks);

  using TDATA = std::string;
  using THASH = std::string;
  using blocks_t = std::vector<Block>;
  using json = nlohmann::json;

  blocks_t bc;
  uint32_t difficulty = 3;

 public:
  Blockchain() = default;

  Blockchain(Blockchain const& other) = default;
  Blockchain(Blockchain&& other) = default;

  Blockchain& operator=(Blockchain const& other) = default;
  Blockchain& operator=(Blockchain&& other) = default;

  auto getBlocks() -> blocks_t const&;

  void push(TDATA data);
  bool isValid();
  void makeValid();

  Block front();
  Block end();

  size_t size();
  bool empty();
  size_t nextId();

  TDATA find(size_t position);
  void edit(size_t position, TDATA data);
  void clear();

  ~Blockchain() = default;
};

void to_json(nlohmann::json& j, Blockchain const& blocks);
void from_json(const nlohmann::json& j, Blockchain& blocks);

auto blockchainFromFile(std::string const& filepath) -> Blockchain;
