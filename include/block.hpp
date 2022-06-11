#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include "sha256.hpp"

using namespace std;

const string hashZeros = "0000000000000000000000000000000000000000000000000000000000000000";
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

  auto getHash() -> string;

  auto getPrevHash() -> string;

  auto calculateHash() -> string;

  auto mineBlock(uint32_t nDifficulty) -> void;

  // auto toJson() -> void;

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
