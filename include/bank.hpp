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

  User() {}
  User(string dni, string name, string password) : dni{dni}, name{name}, password{password} {}
};

auto to_json(json& j, User const& p) -> void;
auto from_json(json const& j, User& p) -> void;

class Bank {
 private:
  using operations_t = std::vector<BankOperation>;
  using users_t = unordered_map<string, User>;

  users_t m_users;
  std::vector<BankOperation> m_operations;

  std::unordered_map<std::string, std::vector<size_t>> m_search_by_type;
  std::unordered_map<std::string, std::vector<size_t>> m_search_by_id_user;

 public:
  Bank() = default;
  auto serialize(string filename) -> bool;

  auto getOperations() -> operations_t const& { return m_operations; }

  auto pushOperation(BankOperation bop) -> void {
    std::visit(overload{[&](auto& bo) { bo.id = this->nextOperationId(); }},
               bop);

    auto& op = m_operations.emplace_back(std::move(bop));

    m_search_by_type[get_type(op)].push_back(m_operations.size() - 1);

    std::string const& id_user = std::visit(
        [](auto const& bo) -> std::string const& { return bo.id_user; }, op);
    m_search_by_id_user[id_user].push_back(m_operations.size() - 1);
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

    std::vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i));
    }
    return res;
  }

  auto searchByIdUser(std::string const& id_user)
      -> std::vector<BankOperation const*> {
    auto it = m_search_by_id_user.find(id_user);
    if (it == m_search_by_type.end()) {
      return {};
    }

    std::vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i));
    }
    return res;
  }

  auto nextOperationId() const -> size_t { return m_operations.size(); }
};
