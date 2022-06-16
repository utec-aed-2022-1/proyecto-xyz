#include "block.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <string>

#include "sha256.hpp"
#include "util.hpp"

using json = nlohmann::json;

auto to_json(json& j, Block const& blk) -> void {
  j = json{{"id", blk.id},
           {"nonce", blk.nonce},
           {"data", blk.data},
           {"prev", blk.prevHash},
           {"hash", blk.hash}};
}

auto from_json(const json& j, Block& blk) -> void {
  j.at("id").get_to(blk.id);
  j.at("nonce").get_to(blk.nonce);
  j.at("data").get_to(blk.data);
  j.at("prev").get_to(blk.prevHash);
  j.at("hash").get_to(blk.hash);
}

auto blockFromFile(string const& filepath) -> Block {
  ifstream fp{filepath};
  json j;
  fp >> j;
  return j.get<Block>();
}

auto toJson(Block const& bl) -> json {
  json j;

  j["id"] = bl.id;
  j["nonce"] = bl.nonce;
  j["data"] = bl.data;
  j["prevHash"] = bl.prevHash;
  j["hash"] = bl.hash;

  return j;
}

auto Block::operator==(Block const& other) const -> bool {
  return id == other.id && data == other.data && nonce == other.nonce &&
         hash == other.hash && prevHash == other.prevHash;
}

auto operator<<(ostream& os, Block const& blck) -> ostream& {
  os << "id: " << blck.id << " \ndata: " << blck.data
     << " \nnonce: " << blck.nonce << " \nprevHash: " << blck.prevHash
     << " \nhash: " << blck.hash;
  return os;
}

auto Block::getId() -> uint64_t { return id; }
auto Block::getData() -> string const& { return data; }
auto Block::getNonce() -> uint64_t { return nonce; }
auto Block::getHash() -> string const& { return hash; }
auto Block::getPrevHash() -> string const& { return prevHash; }

auto Block::calculateHash() -> string {
  return sha256_hex(id, nonce, data, prevHash);
}

auto Block::updateHash() -> void { hash = calculateHash(); }

auto Block::isValid(uint32_t difficulty) -> bool {
  return all_of(this->hash.begin(), next(this->hash.begin(), difficulty),
                [](char c) { return c == '0'; });
}

auto Block::mine(uint32_t difficulty) -> void {
  updateHash();
  if (isValid(difficulty)) {
    return;
  }

  nonce = 0;
  updateHash();

  while (!this->isValid(difficulty)) {
    ++nonce;
    updateHash();
  }
}

auto Block::mineBlock(uint32_t nDifficulty) -> json {
  mine(nDifficulty);

  json dataJson = toJson(*this);

  cout << "nDifficulty: " << nDifficulty << endl;
  cout << "nonce: " << nonce << endl;
  cout << "hash: " << hash << endl;

  return dataJson;
}

auto Block::saveInJson(string const& filepath) -> void {
  jsonToFile(filepath, json(*this));
}
