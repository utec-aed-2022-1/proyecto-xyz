#pragma once

#include <array>
#include <iostream>
#include <string>

#include "../include/json.hpp"
#include "sha256.hpp"

using json = nlohmann::json;
using namespace std;

const string hashZeros =
    "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaultVal = -1;

auto sha256(uint64_t id, string const& data, uint64_t nonce,
            string const& prev_hash) -> array<uint32_t, 8>;

struct block {
  uint64_t id;
  string data;
  uint64_t nonce;
  string hash;
  string prevHash;

  block(uint64_t id, string data) : id(id), data(data) {
    nonce = nonceDefaultVal;
    hash = hashZeros;
    prevHash = hashZeros;
  }

  // block(uint64_t id, string data, string prevHash) : id(id), data(data),
  // prevHash(prevHash) {
  //   nonce = nonceDefaultVal;
  //   hash = hashZeros;
  // }

  // block(uint64_t id, string data, string prevHash, uint64_t nonce) : id(id),
  // data(data), prevHash(prevHash), nonce(nonce) {
  //   hash = hashZeros;
  // }

  auto getHash() -> string;

  auto getPrevHash() -> string;

  auto calculateHash() -> string;

  auto mineBlock(uint32_t nDifficulty) -> json;

  auto saveInJson(json jsxn) -> void;

  // friend auto sha256_(block const& bl) -> array<uint32_t, 8> {
  //   std::cout << "id: " << bl.id << "\ndata: " << bl.data
  //             << "\nnonce: " << bl.nonce << "\nprevhash: " << bl.prevHash;

  //   // ostringstream oss;
  //   // oss << "id" << bl.id << "data" << bl.data << "nonce" << bl.nonce
  //   //     << "prevhash" << bl.prevHash;
  //   return sha256(bl.id, bl.data, bl.nonce, bl.prevHash);
  // }
};

// auto sha256(uint64_t id, string const& data, uint64_t nonce,
//             string const& prev_hash) -> array<uint32_t, 8> {
//   ostringstream oss;
//   oss << "id" << id << "data" << data << "nonce" << nonce << "prevhash"
//       << prev_hash;
//   return sha256(oss.str());
// }
