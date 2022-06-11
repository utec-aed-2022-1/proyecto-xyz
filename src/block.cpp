#include "../include/block.hpp"

auto toJson(Block const& bl) -> json {
  json j;

  j["id"] = bl.id;
  if (bl.nonce != nonceDefaultVal) j["nonce"] = bl.nonce;
  j["data"] = bl.data;
  j["prev"] = bl.prevHash;
  if (bl.hash != hashZeros) j["hash"] = bl.hash;

  return j;
}

auto jsonToFile(json jsxn) -> void {
  mkdir("blocksRegister", 0777);
  string file = "blocksRegister/" + to_string(jsxn["id"]) + ".json";
  ofstream jsonFile(file);  // writing to a file
  if (jsonFile.is_open()) {
    jsonFile << jsxn << endl;
    jsonFile.close();
  } else
    cout << "Unable to open file";
}

auto Block::getHash() -> string { return hash; }

auto Block::getPrevHash() -> string { return prevHash; }

auto Block::calculateHash() -> string {
  json idData = toJson(*this);
  string data = to_string(idData["id"]) + to_string(idData["data"]);

  return sha256_hex(data);
}


auto Block::mineBlock(uint32_t nDifficulty) -> json {
  char* strHash = new char[nDifficulty + 1];
  for (uint32_t i = 0; i < nDifficulty; ++i) strHash[i] = '0';

  strHash[nDifficulty] = '\0';
  string str(strHash);

  do {
    json dataJson = toJson(*this);
    string pureData = to_string(dataJson["id"]) + to_string(dataJson["data"]) +
                      to_string(dataJson["prevHash"]) +
                      to_string(dataJson["nonce"]);
    nonce++;
    hash = sha256_hex(pureData);
    // cout << "nonce: " << nonce << endl;
    // cout << "hash: " << hash << endl;
  } while (hash.substr(0, nDifficulty) != str);

  json dataJson = toJson(*this);

  cout << "nDifficulty: " << nDifficulty << endl;
  cout << "nonce: " << nonce << endl;
  cout << "hash: " << hash << endl;

  return dataJson;
}

auto Block::saveInJson(json jsxn) -> void { jsonToFile(jsxn); }
