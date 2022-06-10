#include <cstdint>
#include <iostream>
#include <sstream>

#include "../include/sha256.hpp"
#include "../include/block.hpp"

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

  // sha256_hex<block>(*this);

  return "sha256_hex(this)";
}