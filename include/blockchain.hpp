#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "block.hpp"
#include "json.hpp"

class Blockchain {
 private:
  using Block = Block;
  friend void to_json(nlohmann::json& j, Blockchain const& blocks);
  friend void from_json(const nlohmann::json& j, Blockchain& blocks);

  using TDATA = std::string;
  using THASH = std::string;
  using blocks_t = std::vector<Block>;
  using json = nlohmann::json;

  blocks_t bc;
  uint32_t difficulty = 3;
  std::string jsonfile = "mainjson.json";

 public:
  Blockchain() = default;
  explicit Blockchain(bool deserialize);
  explicit Blockchain(const std::string& filename);

  auto getBlocks() -> blocks_t const&;

  bool serialize(const std::string& filename = "mainjson.json");
  bool deserialize(const std::string& filename = "mainjson.json");
  bool push(TDATA data);
  bool push(json data);
  Block front();
  Block end();
  int size();
  TDATA find(int position);
  bool edit(int position, TDATA data);
  void clear();

  ~Blockchain();
};

void to_json(nlohmann::json& j, Blockchain const& blocks);
void from_json(const nlohmann::json& j, Blockchain& blocks);

auto blockchainFromFile(std::string const& filepath) -> Blockchain;
