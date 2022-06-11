#include <iostream>

#include "../include/block.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

auto toJson(block const& bl) -> json {
  json j;

  j["id"] = bl.id;
  if(bl.nonce != nonceDefaultVal)
    j["nonce"] = bl.nonce;
  j["data"] = bl.data;
  if(bl.prevHash != hashZeros)
    j["prev"] = bl.prevHash;
  if(bl.hash != hashZeros)
    j["hash"] = bl.hash;

  return j;
}

auto block::getHash() -> string {
  return hash;
}

auto block::getPrevHash() -> string {
  return prevHash;
}

auto block::calculateHash() -> string {
  cout << "calculateHash(): "<< endl;

  json idData = toJson(*this);
  cout << idData << endl;

  string data = to_string(idData["id"]) + to_string(idData["data"]);

  return sha256_hex(data);
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

// auto block::toJson() -> void {
//   json j;
//   j["id"] = this->id;
//   j["nonce"] = this->nonce;
//   j["data"] = this->data;
//   j["prev"] = this->prevHash;
//   j["hash"] = this->hash;

//   cout << j << endl;  
// }