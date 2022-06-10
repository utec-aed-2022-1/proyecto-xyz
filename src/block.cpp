#include <cstdint>
#include <iostream>
#include <sstream>

#include "../include/sha256.hpp"
#include "../include/block.hpp"
#include "../include/json.hpp"

using namespace std;

auto block::getHash() -> string {
  return hash;
}

auto block::getPrevHash() -> string {
  return prevHash;
}

auto block::calculateHash() -> string {
  cout << "calculateHash(): " << this->id << endl;
  // stringstream ss;
  // ss << id << data << nonce << prevHash;

  // sha256_hex<block>(this);

  return "sha256_hex(this)";
}

auto block::mineBlock(uint32_t nDifficulty) -> void {
  // char *strHash = new char[nDifficulty + 1];
  // for (uint32_t i = 0; i < nDifficulty; ++i)
  //   strHash[i] = '0';

  // strHash[nDifficulty] = '\0';

  // string str(strHash);

  // do {
  //   nonce++;
  //   hash = calculateHash();
  // } while (hash.substr(0, nDifficulty) != str);

  cout << "Block mined: " << hash << endl;
}

auto toJson() -> void {
  // json j;
}