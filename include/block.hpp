#pragma once

#include <array>
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

  auto calculateHash() -> string;

  // void mineBlock(uint32_t nDifficulty) {
  //   char *strHash = new char[nDifficulty + 1];
  //   for (uint32_t i = 0; i < nDifficulty; ++i)
  //     strHash[i] = '0';

  //   strHash[nDifficulty] = '\0';

  //   string str(strHash);

  //   do {
  //     nonce++;
  //     hash = calculateHash();
  //   } while (hash.substr(0, nDifficulty) != str);

  //   cout << "Block mined: " << hash << endl;
  // }

 public:
  friend auto sha256(block const& bl) -> std::array<uint32_t, 8> {
    std::ostringstream oss;
    oss << "id" << bl.id << "data" << bl.data << "nonce" << bl.nonce
        << "prevhash" << bl.prevHash;
    return sha256(oss.str());
  }
};
