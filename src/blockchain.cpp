//
// Created by Mauricio on 9/06/2022.
//

#include "../include/blockchain.hpp"

#include <utility>

#include "json.hpp"

using json = nlohmann::json;

void to_json(json& j, Blockchain const& blocks) { j = json{blocks.bc}; }
void from_json(const json& j, Blockchain& blocks) { j.get_to(blocks.bc); }

Blockchain::Blockchain(bool deserialize) {
  if (deserialize) {
    if (!this->deserialize(jsonfile))
      throw std::invalid_argument("Deserialize failed");
  }
}

Blockchain::Blockchain(const std::string& filename) {
  if (!this->deserialize(filename))
    throw std::invalid_argument("Deserialize failed");
}

bool Blockchain::serialize(const std::string& filename) {
  std::ofstream file(filename, std::ofstream::trunc);

  if (file.fail()) {
    // File does not exist code here
    cout << "This file does not exist" << endl;
    return false;
  }

  file << "{\n  \"data\": [\n";
  unsigned long long number = 0;
  for (auto& x : this->bc) {
    json jxsn;
    jxsn["id"] = x.id;
    jxsn["data"] = x.data;
    jxsn["prev"] = x.prevHash;
    jxsn["nonce"] = x.nonce;
    jxsn["hash"] = x.hash;

    std::string str = jxsn.dump(4);
    file << str;
    if (number != this->bc.size() - 1) file << ",\n";

    number++;
  }
  file << "\n  ]\n}";

  file.close();
  return true;
}

bool Blockchain::deserialize(const std::string& filename) {
  // read json main file
  std::ifstream file(filename, std::ifstream::in);

  if (file.fail()) {
    // File does not exist code here
    cout << "This file does not exist" << endl;
    return false;
  }

  char c = file.get();
  std::string to_json;
  while (file.good()) {  // TODO: No funciona con el operador sobrecargado <<,
    // puede no ser la forma mas eficiente
    to_json += c;
    c = file.get();
  }
  json j = json::parse(to_json);

  for (int i = 0; i < j["data"].size(); i++) {
    Block blck(j["data"][i]["id"], j["data"][i]["data"], j["data"][i]["prev"],
               j["data"][i]["nonce"], j["data"][i]["hash"]);
    this->bc.push_back(blck);
  }
  for (auto& x : this->bc) {
    // TODO: verificar hash llamando a la función
    // cout<<x.getHash()<<endl;
  }
  file.close();
  return true;
}

void Blockchain::clear() { this->bc.clear(); }

Blockchain::~Blockchain() {
  serialize();
  this->bc.clear();
}
