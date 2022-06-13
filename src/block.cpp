#include "block.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <string>

#include "sha256.hpp"

using json = nlohmann::json;

void to_json(json& j, Block const& blk) {
  j = json{{"id", blk.id},
           {"nonce", blk.nonce},
           {"data", blk.data},
           {"prev", blk.prevHash},
           {"hash", blk.hash}};
}

void from_json(const json& j, Block& blk) {
  j.at("id").get_to(blk.id);
  j.at("nonce").get_to(blk.nonce);
  j.at("data").get_to(blk.data);
  j.at("prev").get_to(blk.prevHash);
  j.at("hash").get_to(blk.hash);
}

auto blockFromFile(std::string const& filepath) -> Block {
  std::ifstream fp{filepath};
  json j;
  fp >> j;
  return j.get<Block>();
}

auto toJson(Block const& bl) -> json {
  json j;

  j["id"] = bl.id;
  if (bl.nonce != nonceDefaultVal) j["nonce"] = bl.nonce;
  j["data"] = bl.data;
  j["prev"] = bl.prevHash;
  if (bl.hash != hashZeros) j["hash"] = bl.hash;

  return j;
}

auto Block::getId() -> uint64_t { return this->id; }
auto Block::getData() -> string const& { return this->data; }
auto Block::getNonce() -> uint64_t { return this->nonce; }
auto Block::getHash() -> string const& { return hash; }
auto Block::getPrevHash() -> string const& { return prevHash; }

auto Block::calculateHash() -> string {
  return sha256_hex(this->id, this->nonce, this->data, this->prevHash);
}

void Block::updateHash() {
  this->hash = sha256_hex(this->id, this->nonce, this->data, this->prevHash);
}

void Block::mine(uint32_t difficulty) {
  nonce = 0;
  this->updateHash();

  while (std::any_of(hash.begin(), std::next(hash.begin(), difficulty),
                     [](char c) { return c != '0'; })) {
    ++nonce;
    this->updateHash();
  }
}

auto Block::mineBlock(uint32_t nDifficulty) -> json {
  char* strHash = new char[nDifficulty + 1];
  for (uint32_t i = 0; i < nDifficulty; ++i) strHash[i] = '0';

  strHash[nDifficulty] = '\0';
  string str(strHash);
  delete []strHash;

  do {
    json dataJson = toJson(*this);
    string pureData = to_string(dataJson["id"]) + to_string(dataJson["data"]) +
                      to_string(dataJson["prevHash"]) +
                      to_string(dataJson["nonce"]);
    nonce++;
    hash = sha256_hex(pureData);
    // cout << "nonce: " << nonce << endl;
    // cout << "hash: " << hash << endl;
  } while (hash.substr(0, nDifficulty) != str);

  json dataJson = toJson(*this);

  cout << "nDifficulty: " << nDifficulty << endl;
  cout << "nonce: " << nonce << endl;
  cout << "hash: " << hash << endl;

  return dataJson;
}

auto Block::saveInJson(json jsxn) -> void { jsonToFile(jsxn); }
