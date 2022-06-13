#include "../include/block.hpp"

auto toJson(Block const& bl) -> json {
  json j;

  j["id"] = bl.id;
  j["nonce"] = bl.nonce;
  j["data"] = bl.data;
  j["prevHash"] = bl.prevHash;
  j["hash"] = bl.hash;

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
  json dataJson = toJson(*this);

  ostringstream oss;

  oss << dataJson["id"].get<uint64_t>() << dataJson["data"].get<string>()
      << dataJson["prevHash"].get<string>()
      << dataJson["nonce"].get<uint64_t>();

  return sha256_hex(oss.str());
}

auto Block::mineBlock(uint32_t nDifficulty) -> json {
  char* strHash = new char[nDifficulty + 1];
  for (uint32_t i = 0; i < nDifficulty; ++i) strHash[i] = '0';

  strHash[nDifficulty] = '\0';
  string str(strHash);
  delete[] strHash;

  do {
    json dataJson = toJson(*this);
    ostringstream oss;

    oss << dataJson["id"].get<uint64_t>() << dataJson["data"].get<string>()
        << dataJson["prevHash"].get<string>()
        << dataJson["nonce"].get<uint64_t>();
    nonce++;
    hash = sha256_hex(oss.str());
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
