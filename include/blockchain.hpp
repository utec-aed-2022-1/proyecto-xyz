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
  std::string jsonfile = "mainjson.json";
  bool valid_bc = false;
  bool destructionserialize = false;

  bool deserialize_private(std::string filename);
  bool serialize_private(std::string filename);
  void push(json data, size_t diferenciador);

 public:
  Blockchain() = default;
  explicit Blockchain(bool deserialize, bool deserialize_);
  Blockchain(std::string filename);

  auto getBlocks() -> blocks_t const&;

  bool serialize(std::string filename);
  bool deserialize(std::string filename);
  void push(TDATA data);
  void push(std::string filename, bool isfile);
  void setserializedestruction(bool destructionserialize_);
  Block front();
  Block end();
  size_t size();
  TDATA find(size_t position);
  bool edit(size_t position, TDATA data);
  void clear();

  ~Blockchain();
};

void to_json(nlohmann::json& j, Blockchain const& blocks);
void from_json(const nlohmann::json& j, Blockchain& blocks);

auto blockchainFromFile(std::string const& filepath) -> Blockchain;
