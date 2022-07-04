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
  string dni;
  string name;
  string password;
};

auto to_json(json& j, User const& p) -> void;
auto from_json(json const& j, User& p) -> void;

class Bank {
 private:
  using operations_t = std::vector<BankOperation>;
  using users_t = unordered_map<string, User>;

  users_t m_users;
  std::vector<BankOperation> m_operations;

  std::unordered_map<std::string, std::vector<BankOperation const*>>
      m_search_by_type;

 public:
  Bank() = default;
  auto serialize(string filename) -> bool;

  auto getOperations() -> operations_t const& { return m_operations; }

  auto pushOperation(BankOperation bop) -> void {
    auto const& op = m_operations.emplace_back(std::move(bop));
    m_search_by_type[get_type(op)].push_back(&op);
  }

  auto addUser(User p) -> void { m_users[p.dni] = std::move(p); }

  auto getUser(std::string const& key) -> User const& {
    return m_users.at(key);
  }
  auto getUsers() -> users_t const& { return m_users; }

  auto searchByType(std::string const& type)
      -> std::vector<BankOperation const*> {
    auto it = m_search_by_type.find(type);
    if (it == m_search_by_type.end()) {
      return {};
    }
    return it->second;
  }
};
