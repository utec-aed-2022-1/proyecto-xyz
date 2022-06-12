//
// Created by Mauricio on 9/06/2022.
//

#include "../include/blockchain.hpp"

Blockchain::Blockchain(bool deserialize) {
  if (deserialize) {
    // read json main faile
    std::ifstream file(jsonfile, std::ifstream::in);

    if (file.fail()) {
      // File does not exist code here
      cout << "This file does not exist" << endl;
      throw std::invalid_argument("This file does not exist");
    }

    char c = file.get();
    std::string to_json;
    while (file.good()) {  // TODO: No funciona con el operador sobrecargado <<,
                           // puede no ser la forma mas eficiente
      to_json += c;
      c = file.get();
    }
    json j = json::parse(to_json);

    std::cout << j.dump(2) << endl;
    file.close();
  }
}

Blockchain::~Blockchain() {
  // TODO
  cout << "Destructor" << endl;
}
