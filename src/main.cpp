#include <array>
#include <iostream>

#include "../include/json.hpp"
#include "block.hpp"
#include "blockchain.hpp"
#include "sha256.hpp"

using json = nlohmann::json;
using namespace std;

auto main() -> int {
  // from console
  Block blck(1, "Hello World");

  // cout << blck.getHash() << endl;
  // cout << blck.getPrevHash() << endl;

  cout << "Hash inicial (id y data): " << endl;
  cout << blck.calculateHash() << endl;

  cout << "Mina el bloque: " << endl;
  json jsxn = blck.mineBlock(3);

  blck.saveInJson(jsxn);

  // from json file (falta implementar cuando hay más de 1 registro)
  // Block blck("blocksInput/1.json");
  // cout << blck.calculateHash() << endl;

  // cout << "Mina el bloque: " << endl;
  // json jsxn = blck.mineBlock(3);

  // blck.saveInJson(jsxn);

  Blockchain A;
  return 0;
}
