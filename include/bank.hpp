#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

#include "json.hpp"
#include "util.hpp"

using namespace std;
using json = nlohmann::json;

struct User {
  size_t id;
  string dni;
  string name;
  string password;
};

auto user_to_json(json& j, const User& p) -> void;
auto user_from_json(const json& j, User& p) -> void;

class Bank {
 private:
  unordered_map<string, User> users;

 public:
  Bank() = default;
  auto serialize(string filename) -> bool;
};
