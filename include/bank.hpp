#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "bank_operations.hpp"
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

auto to_json(json& j, User const& p) -> void;
auto from_json(json const& j, User& p) -> void;

class Bank {
 private:
  using operations_t = std::vector<BankOperation>;

  unordered_map<string, User> m_users;
  std::vector<BankOperation> m_operations;

 public:
  Bank() = default;
  auto serialize(string filename) -> bool;

  auto getOperations() -> operations_t const& { return m_operations; }

  auto pushOperation(BankOperation bop) -> void {
    m_operations.emplace_back(std::move(bop));
  }

  auto addUser(User p) -> void { m_users[p.dni] = std::move(p); }
};
