#pragma once

#include <sys/stat.h>
#include <sys/types.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
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

struct Block {
  uint64_t id{0};
  string data{""};
  uint64_t nonce{0};
  string hash{hashZeros};
  string prevHash{hashZeros};
  string jsxn;

  // auto readFromJson(string pathFile) -> Block;

  Block() = default;

  Block(uint64_t id, string data) : id(id), data(data) {
    nonce = nonceDefaultVal;
    hash = hashZeros;
    prevHash = hashZeros;
  }

  Block(string jsxn) : jsxn(jsxn) { readFromJson(jsxn, *this); }

  Block(uint64_t id, string data, uint64_t nonce, string prevHash,
        string hash = "")
      : id(id),
        data(move(data)),
        nonce(nonce),
        hash(move(hash)),
        prevHash(move(prevHash)) {
    ;
  }

  auto operator==(Block const& other) const -> bool;

  auto getId() -> uint64_t;
  auto getData() -> string const&;
  auto getNonce() -> uint64_t;
  auto getHash() -> string const&;
  auto getPrevHash() -> string const&;

  auto calculateHash() -> string;
  auto updateHash() -> void;

  auto isValid(uint32_t difficulty) -> bool;
  auto mine(uint32_t difficulty) -> void;

  auto mineBlock(uint32_t nDifficulty) -> json;

  auto saveInJson(string const& filepath) -> void;

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
};

auto to_json(json& j, Block const& blk) -> void;
auto from_json(const json& j, Block& blk) -> void;

auto blockFromFile(string const& filepath) -> Block;
