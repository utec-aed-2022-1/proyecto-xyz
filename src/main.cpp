#include <array>
#include <iostream>

#include "blockchain.hpp"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

auto main() -> int { /*
   // from console
   Block blck(1, "Hello World");

   // cout << blck.getHash() << endl;
   // cout << blck.getPrevHash() << endl;

   cout << "Hash inicial (id y data): " << endl;
   cout << blck.calculateHash() << endl;

   cout << "Mina el bloque: " << endl;
   json jsxn = blck.mineBlock(3);

<<<<<<< Updated upstream
  blck.saveInJson("aa/file.json");
=======
   blck.saveInJson(jsxn);*/
>>>>>>> Stashed changes

  // from json file (falta implementar cuando hay más de 1 registro)
  // Block blck("blocksInput/1.json");
  // cout << blck.calculateHash() << endl;

  // cout << "Mina el bloque: " << endl;
  // json jsxn = blck.mineBlock(3);

  // blck.saveInJson(jsxn);
  Blockchain A("mainjson.json");
  A.setserializedestruction(true);
  A.push("camila-prestamo: 50$");
  A.push("jefferson-prestamo: 10000$");
  A.push("maria-prestamo: 1240$");
  A.push("1.json", true);
  A.edit(3, "itsme Mario aksdalda");
  A.serialize("mainjson.json");
  cout << "Size: " << A.size() << endl;
  cout << "Find: " << A.find(3) << endl;
  return 0;
}
