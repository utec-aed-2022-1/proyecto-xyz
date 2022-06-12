#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "block.hpp"
#include "json.hpp"

class Blockchain {
 private:
  using block = std::string;
  using TDATA = std::string;
  using THASH = std::string;
  using vector = std::vector<Block>;
  using json = nlohmann::json;

  vector bc;
  std::string jsonfile = "mainjson.json";

 public:
  Blockchain(bool deserialize = true);
  Blockchain(std::string jsonfile);

  bool serialize();
  bool deserialize();
  bool push(TDATA data);
  block front();
  block end();
  TDATA find(int position);
  bool edit(int position, TDATA data);
  bool clean();

  ~Blockchain();
};
