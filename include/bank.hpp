#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

#include "json.hpp"
#include "util.hpp"

using namespace std;
using json = nlohmann::json;

struct User {
  size_t id;
  string dni;
  string name;
  string password;

  User(size_t id, string dni, string name, string password) : id{id}, dni{dni}, name{name}, password{password} {}
};

auto to_json(json& j, User const& p) -> void;
auto from_json(json const& j, User& p) -> void;

class Bank {
 private:
  unordered_map<string, User> users;

 public:
  Bank() = default;
  auto serialize(string filepath) -> bool;
  auto deserialize(json jsxn, string filepath) -> bool;
};
