//
// Created by Mauricio on 9/06/2022.
//

#include "blockchain.hpp"

#include <utility>

#include "json.hpp"

using json = nlohmann::json;
using TDATA = std::string;

void to_json(json& j, Blockchain const& blocks) { j = json{blocks.bc}; }
void from_json(const json& j, Blockchain& blocks) { j.get_to(blocks.bc); }

auto blockchainFromFile(std::string const& filepath) -> Blockchain {
  std::ifstream fp{filepath};
  json j;
  fp >> j;
  return j.get<Blockchain>();
}

Blockchain::Blockchain(bool deserialize, bool deserialize_) {
  if (deserialize && deserialize_) {
    if (!this->deserialize_private(jsonfile)) {
      cout << "Deserialize ha fallado" << endl;  // TODO: rethink
      this->valid_bc = false;
    } else
      this->valid_bc = true;
  }
}

Blockchain::Blockchain(std::string filename) {
  if (!this->deserialize(filename)) {
    cout << "Deserialize ha fallado" << endl;  // TODO: found a better way
    this->valid_bc = false;
  } else {
    this->valid_bc = true;
  }
}

auto Blockchain::getBlocks() -> blocks_t const& { return this->bc; }

bool Blockchain::serialize_private(std::string filename) {
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

bool Blockchain::serialize(std::string filename) {
  if (!this->valid_bc) {
    filename = "invalid" + filename;
    cout << "This blockchain is not valid to serialize,"
            " alternative serialize made in "
         << filename << endl;
  }

  filename = "blocksRegister/" + filename;
  return serialize_private(filename);
}

bool Blockchain::deserialize_private(std::string filename) {
  // read json main file
  std::ifstream file(filename, std::ifstream::in);

  if (file.fail()) {
    // File does not exist code here
    cout << "This file does not exist" << endl;
    return false;
  }

  // deserialize
  char c = file.get();
  std::string to_json;
  while (file.good()) {  // TODO: No funciona con el operador sobrecargado <<,
    // puede no ser la forma mas eficiente
    to_json += c;
    c = file.get();
  }
  json j = json::parse(to_json);

  for (int i = 0; i < j["data"].size(); i++) {
    Block blck(j["data"][i]["id"], j["data"][i]["data"], j["data"][i]["nonce"],
               j["data"][i]["prev"], j["data"][i]["hash"]);

    this->bc.push_back(blck);
  }

  // verificar si el archivo leido es valido
  bool flag = false;
  for (size_t i = 0; i < this->bc.size(); i++) {
    std::string temp_hash = this->bc[i].hash;
    uint64_t temp_nonce = this->bc[i].nonce;
    std::string temp_prev;
    if (i == 0)
      temp_prev = hashZeros;
    else
      temp_prev = this->bc[i].prevHash;
    uint64_t temp_id = i + 1;

    this->bc[i].nonce = nonceDefaultVal;
    this->bc[i].mineBlock(this->difficulty);

    if (this->bc[i].hash != temp_hash || this->bc[i].nonce != temp_nonce ||
        this->bc[i].prevHash != temp_prev || this->bc[i].id != temp_id) {
      cout << "Mineblock found different values of hash or nonce or prev or id "
              "in ";
      cout << i << " block." << endl;
      this->bc[i].nonce = temp_nonce;
      this->bc[i].hash = temp_hash;
      flag = true;
    } else {
      this->bc[i].nonce = temp_nonce;
    }
  }
  file.close();
  if (flag) return false;
  return true;
}

bool Blockchain::deserialize(std::string filename) {
  filename = "blocksinput/" + filename;
  if (filename == this->jsonfile) {
    cout << "This is an invalid name, try again" << endl;
    return false;
  } else
    return this->deserialize_private(filename);
}

void Blockchain::push(TDATA data) {
  json j;
  j["data"] = data;
  this->push(j, 1);
}

void Blockchain::push(std::string filename, bool isfile) {
  if (!isfile) cout << "fichero que no es un fichero ingresado" << endl;
  // read json file
  filename = "blocksinput/" + filename;
  std::ifstream file(filename, std::ifstream::in);

  if (file.fail()) {
    // File does not exist code here
    cout << "This file does not exist" << endl;
    return;
  }

  // deserialize
  char c = file.get();
  std::string to_json;
  while (file.good()) {  // TODO: No funciona con el operador sobrecargado <<,
    // puede no ser la forma mas eficiente
    to_json += c;
    c = file.get();
  }
  json j = json::parse(to_json);

  this->push(j, 1);

  file.close();
}

void Blockchain::push(json data, int diferenciador) {
  Block blck(this->bc.size() + 1, data["data"]);
  if (!this->bc.empty()) blck.prevHash = this->bc.back().hash;

  this->valid_bc = true;
  blck.mineBlock(difficulty);
  this->bc.push_back(blck);
}

Block Blockchain::front() { return this->bc.front(); }

Block Blockchain::end() { return this->bc.back(); }

void Blockchain::setserializedestruction(bool destructionserialize_) {
  this->destructionserialize = destructionserialize_;
}

size_t Blockchain::size() { return this->bc.size(); }

TDATA Blockchain::find(int position) {
  if (position >= this->size() || position < 0) {
    throw std::invalid_argument("find: index out of range");
  }

  return this->bc[position].data;
}

bool Blockchain::edit(int position, TDATA data) {
  if (position >= this->size() || position < 0) {
    return false;
  }

  this->bc[position].data = data;
  for (size_t i = position; i < this->bc.size(); i++) {
    this->bc[position].nonce = nonceDefaultVal;
    this->bc[position].mineBlock(this->difficulty);
  }
  return true;
}

void Blockchain::clear() { this->bc.clear(); }

Blockchain::~Blockchain() {
  if (this->destructionserialize) {
    if (!this->valid_bc)
      cout << "This blockchain is not valid to serialize"
              " when destructor is called";
    else
      serialize_private(this->jsonfile);
  }

  this->bc.clear();
}
