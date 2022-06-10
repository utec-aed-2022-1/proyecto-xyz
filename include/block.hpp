#pragma once

#include <string>
#define hashZeros "0000000000000000000000000000000000000000000000000000000000000000";

using namespace std;

class block {
private:
  uint64_t id;
  string data;
  uint64_t nonce;

public:
  string hash;
  string prevHash;

  block(uint64_t id, string data) : id(id), data(data) { 
    nonce = -1; 
    hash = hashZeros;
    prevHash = hashZeros;
  }

  auto getHash() -> string;

  auto getPrevHash() -> string;

  auto calculateHash() -> string;

  auto mineBlock(uint32_t nDifficulty) -> void;

  auto toJson() -> void;
};