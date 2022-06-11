#pragma once

#include <array>
#include <iostream>
#include <sstream>
#include <string>

#include "sha256.hpp"

#define hashZeros \
  "0000000000000000000000000000000000000000000000000000000000000000";

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

  auto calculateHash() -> array<uint32_t, 8>;

  auto mineBlock(uint32_t nDifficulty) -> void;

  auto toJson() -> void;

  friend auto sha256_(block const& bl) -> array<uint32_t, 8> {
    std::cout << "id: " << bl.id << "\ndata: " << bl.data
              << "\nnonce: " << bl.nonce << "\nprevhash: " << bl.prevHash;

    ostringstream oss;
    oss << "id" << bl.id << "data" << bl.data << "nonce" << bl.nonce
        << "prevhash" << bl.prevHash;
    return sha256(oss.str());
  }
};
