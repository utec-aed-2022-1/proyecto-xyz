#pragma once

#include <string>

class blockchain {
 private:
  using block = std::string;
  using TDATA = std::string;
  using THASH = std::string;
  using vector = Vector;

  vector<block> bc;

 public:
  blockchain();
  blockchain(json data);

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
