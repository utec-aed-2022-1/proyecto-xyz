#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>

#include "../include/block.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

auto block::getHash() -> string {
  return hash;
}

auto block::getPrevHash() -> string {
  return prevHash;
}

auto block::calculateHash() -> array<uint32_t, 8> {
  cout << "calculateHash(): " << this->id << endl;
  // stringstream ss;
  // ss << id << data << nonce << prevHash;

  return sha256_(*this);
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

  cout << "nDifficulty: " << nDifficulty << endl;
  cout << "Block mined: " << hash << endl;
}

auto block::toJson() -> void {
  json j;
  j["id"] = this->id;
  j["nonce"] = this->nonce;
  j["data"] = this->data;
  j["prev"] = this->prevHash;
  j["hash"] = this->hash;

  cout << j << endl;  
}