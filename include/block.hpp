#pragma once

#include <sys/stat.h>
#include <sys/types.h>

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"
#include "sha256.hpp"

using json = nlohmann::json;
using namespace std;

const string hashZeros =
    "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaultVal = -1;

auto sha256(uint64_t id, string const& data, uint64_t nonce,
            string const& prev_hash) -> array<uint32_t, 8>;

struct Block {
  friend void to_json(nlohmann::json& j, Block const& blk);
  friend void from_json(const nlohmann::json& j, Block& blk);

  uint64_t id;
  string data;
  uint64_t nonce;
  string hash;
  string prevHash;
  string jsxn;

  // auto readFromJson(string pathFile) -> Block;

  Block() = default;

  Block(uint64_t id, string data) : id(id), data(data) {
    nonce = nonceDefaultVal;
    hash = hashZeros;
    prevHash = hashZeros;
  }

  Block(string jsxn) : jsxn(jsxn) { readFromJson(jsxn, *this); }

  Block(uint64_t id, string data, string prevHash, uint64_t nonce, string hash)
      : id(id), data(data), prevHash(prevHash), nonce(nonce), hash(hash) {
    ;
  }

  auto getId() -> uint64_t;
  auto getData() -> string const&;
  auto getNonce() -> uint64_t;
  auto getHash() -> string const&;
  auto getPrevHash() -> string const&;

  auto calculateHash() -> string;
  void updateHash();

  void mine(uint32_t difficulty);

  auto mineBlock(uint32_t nDifficulty) -> json;

  auto saveInJson(json jsxn) -> void;

  auto readFromJson(string pathFile, Block& blck) -> void {
    string line;

    ifstream read(pathFile);
    if (read.is_open()) {
      while (!read.eof()) {
        getline(read, line);
        json jsonParsed = json::parse(line);
        blck.id = jsonParsed["id"];
        blck.data = jsonParsed["data"];
      }
      read.close();
    } else
      cout << "Unable to open file";
  }

  // friend auto sha256_(Block const& bl) -> array<uint32_t, 8> {
  //   std::cout << "id: " << bl.id << "\ndata: " << bl.data
  //             << "\nnonce: " << bl.nonce << "\nprevhash: " << bl.prevHash;

  //   // ostringstream oss;
  //   // oss << "id" << bl.id << "data" << bl.data << "nonce" << bl.nonce
  //   //     << "prevhash" << bl.prevHash;
  //   return sha256(bl.id, bl.data, bl.nonce, bl.prevHash);
  // }
};

void to_json(nlohmann::json& j, Block const& blk);
void from_json(const nlohmann::json& j, Block& blk);

auto blockFromFile(std::string const& filepath) -> Block;
