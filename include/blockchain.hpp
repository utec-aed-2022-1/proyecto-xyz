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

 public:
  Blockchain() = default;
  explicit Blockchain(bool deserialize);
  explicit Blockchain(const std::string& filename);

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
