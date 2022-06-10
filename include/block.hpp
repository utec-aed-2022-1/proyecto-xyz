#pragma once

#include <cstdint>
#include <sstream>
#include <string>

#include "sha256.hpp"

using namespace std;

class Block {
 private:
  uint64_t id;
  uint64_t nonce;
  string data;
  string hash;

  // string calculateHash() const {
  //   stringstream ss;
  //   ss << id << data << nonce << prevHash;

  //   return sha256_hex(ss.str());
  // }
 public:
  string prevHash;

  Block(uint64_t id, string data) : id(id), data(data) { nonce = -1; }

  string getHash() { return hash; }

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
};