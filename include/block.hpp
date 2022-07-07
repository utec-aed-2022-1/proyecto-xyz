#pragma once

#include <sys/stat.h>
#include <sys/types.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "json.hpp"
#include "sha256.hpp"
#include "util.hpp"

using json = nlohmann::json;
using namespace std;

const string hashZeros =
    "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaultVal = -1;

template <typename T>
struct Block {
  uint64_t id{0};
  T data{};
  uint64_t nonce{0};
  string hash{hashZeros};
  string prevHash{hashZeros};
  string jsxn;

  Block() = default;

  Block(uint64_t id, T data) : id(id), data(std::move(data)) {
    nonce = nonceDefaultVal;
    hash = hashZeros;
    prevHash = hashZeros;
  }

  Block(uint64_t id, T data, uint64_t nonce, string prevHash, string hash = "")
      : id(id),
        data(move(data)),
        nonce(nonce),
        hash(move(hash)),
        prevHash(move(prevHash)) {
    ;
  }

  auto operator==(Block const& other) const -> bool {
    return id == other.id && data == other.data && nonce == other.nonce &&
           hash == other.hash && prevHash == other.prevHash;
  }

  auto getId() -> uint64_t { return id; }
  auto getData() -> T const& { return data; }
  auto getNonce() -> uint64_t { return nonce; }
  auto getHash() -> string const& { return hash; }
  auto getPrevHash() -> string const& { return prevHash; }

  auto calculateHash() -> string {
    return sha256_hex(id, nonce, data, prevHash);
  }

  auto updateHash() -> void { hash = calculateHash(); }

  auto isValid(uint32_t difficulty) -> bool {
    return all_of(this->hash.begin(), next(this->hash.begin(), difficulty),
                  [](char c) { return c == '0'; });
  }

  auto mine(uint32_t difficulty) -> void {
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

  auto saveInJson(string const& filepath) -> void {
    jsonToFile(filepath, json(*this));
  }

  friend auto operator<<(ostream& os, Block const& blck) -> ostream& {
    os << "id: " << blck.id << " \ndata: " << blck.data
       << " \nnonce: " << blck.nonce << " \nprevHash: " << blck.prevHash
       << " \nhash: " << blck.hash;
    return os;
  }
};

template <typename T>
auto to_json(json& j, Block<T> const& blk) -> void {
  j = json{{"id", blk.id},
           {"nonce", blk.nonce},
           {"data", blk.data},
           {"prev", blk.prevHash},
           {"hash", blk.hash}};
}

template <typename T>
auto from_json(const json& j, Block<T>& blk) -> void {
  j.at("id").get_to(blk.id);
  j.at("nonce").get_to(blk.nonce);
  j.at("data").get_to(blk.data);
  j.at("prev").get_to(blk.prevHash);
  j.at("hash").get_to(blk.hash);
}

template <typename T>
auto blockFromFile(string const& filepath) -> Block<T> {
  ifstream fp{filepath};
  json j;
  fp >> j;
  return j.get<Block<T>>();
}
