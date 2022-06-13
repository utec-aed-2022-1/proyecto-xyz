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
  using TDATA = std::string;
  using THASH = std::string;
  using vector = std::vector<Block>;
  using json = nlohmann::json;

  vector bc;
  uint32_t difficulty = 3;
  std::string jsonfile = "mainjson.json";
  bool valid_bc = false;
  bool destructionserialize = false;

  bool deserialize_private(const std::string& filename);
  bool serialize_private(std::string filename);

 public:
  Blockchain() = default;
  explicit Blockchain(bool deserialize, bool deserialize_);
  Blockchain(std::string filename);

  bool serialize(std::string filename);
  bool deserialize(const std::string& filename);
  bool push(TDATA data);
  bool push(json data);
  void setserializedestruction(bool destructionserialize);
  Block front();
  Block end();
  int size();
  TDATA find(int position);
  bool edit(int position, TDATA data);
  void clear();

  ~Blockchain();
};
