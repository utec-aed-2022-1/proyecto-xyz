#pragma once

#include <string>

#include "block.hpp"

class blockchain {
 private:
  using block = std::string;
  using TDATA = std::string;
  using THASH = std::string;
  using vector = std::vector<block>;

  vector bc;

 public:
  blockchain();
//   blockchain(json data);

  bool serialize();
  bool deserialize();
  bool push(TDATA data);
  block front();
  block end();
  TDATA find(int position);
  bool edit(int position, TDATA data);
  bool clean();

  ~blockchain();
};
