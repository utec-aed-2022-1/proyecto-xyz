#pragma once

#include <iostream>
#include <string>

#include "bank_operations.hpp"
#include "blockchain.hpp"
#include "hash_map.hpp"
#include "json.hpp"
#include "util.hpp"
#include "vector"

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
  using operations_t = Blockchain<BankOperation>;
  using users_t = HashMap<string, User>;

  users_t m_users;
  operations_t m_operations;

  // In all types
  HashMap<size_t, size_t> m_search_by_id;
  HashMap<std::string, Vector<size_t>> m_search_by_type;
  HashMap<std::string, Vector<size_t>> m_search_by_id_user;

  // In some types
  HashMap<std::string, Vector<size_t>> m_search_by_id_client;
  HashMap<std::string, Vector<size_t>> m_search_by_id_sender;
  HashMap<std::string, Vector<size_t>> m_search_by_id_receiver;
  HashMap<std::string, Vector<size_t>> m_search_by_id_seller;

 public:
  Bank() = default;
  auto serialize(string filename) -> bool;

  auto getOperations() -> Vector<BankOperation const*> {
    Vector<BankOperation const*> ret;
    for (auto const& block : m_operations) {
      ret.push_back(&block.data);
    }

    return ret;
  }

  auto pushOperation(BankOperation bop) -> void {
    std::visit(overload{[&](auto& bo) { bo.id = this->nextOperationId(); }},
               bop);

    auto const& op = m_operations.push(std::move(bop)).data;
    size_t last_index = m_operations.size() - 1;

    // TODO: `amount` and `date` are range searches

    m_search_by_type[get_type(op)].push_back(last_index);
    std::visit(
        [&](auto const& bop) {
          m_search_by_id[bop.id] = last_index;
          m_search_by_id_user[bop.id_user].push_back(last_index);
        },
        op);

    std::visit(
        overload{[&](BankWithdrawal const& bw) {
                   m_search_by_id_client[bw.id_client].push_back(last_index);
                 },
                 [&](BankTransfer const& bt) {
                   m_search_by_id_sender[bt.id_sender].push_back(last_index);
                   m_search_by_id_receiver[bt.id_receiver].push_back(
                       last_index);
                 },
                 [&](BankSaleRegister const& bsr) {
                   m_search_by_id_client[bsr.id_client].push_back(last_index);
                   m_search_by_id_seller[bsr.id_seller].push_back(last_index);
                 }},
        op);
  }

  auto addUser(User p) -> void { m_users[p.dni] = std::move(p); }

  auto getUser(std::string const& key) -> User const& {
    return m_users[key];
  }
  auto getUsers() -> users_t const& { return m_users; }

  auto searchByType(std::string const& type) -> Vector<BankOperation const*> {
    auto it = m_search_by_type.find(type);
    if (it == m_search_by_type.end()) {
      return {};
    }

    Vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i).data);
    }
    return res;
  }

  auto searchByIdUser(std::string const& id_user)
      -> Vector<BankOperation const*> {
    auto it = m_search_by_id_user.find(id_user);
    if (it == m_search_by_id_user.end()) {
      return {};
    }

    Vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i).data);
    }
    return res;
  }

  auto searchByIdClient(std::string const& id_client)
      -> Vector<BankOperation const*> {
    auto it = m_search_by_id_client.find(id_client);
    if (it == m_search_by_id_client.end()) {
      return {};
    }

    Vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i).data);
    }
    return res;
  }

  auto searchByIdSender(std::string const& id_sender)
      -> Vector<BankOperation const*> {
    auto it = m_search_by_id_sender.find(id_sender);
    if (it == m_search_by_id_sender.end()) {
      return {};
    }

    Vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i).data);
    }
    return res;
  }

  auto searchByIdReceiver(std::string const& id_receiver)
      -> Vector<BankOperation const*> {
    auto it = m_search_by_id_receiver.find(id_receiver);
    if (it == m_search_by_id_receiver.end()) {
      return {};
    }

    Vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i).data);
    }
    return res;
  }

  auto searchByIdSeller(std::string const& id_seller)
      -> Vector<BankOperation const*> {
    auto it = m_search_by_id_seller.find(id_seller);
    if (it == m_search_by_id_seller.end()) {
      return {};
    }

    Vector<BankOperation const*> res;
    for (size_t i : it->second) {
      res.push_back(&m_operations.at(i).data);
    }
    return res;
  }

  auto nextOperationId() const -> size_t { return m_operations.size(); }

  friend auto to_json(json& j, Bank const& bank) -> void {
    j = json{
        {"operations", bank.m_operations},
        {"users", bank.m_users},
    };
  }

  friend auto from_json(const json& j, Bank& bank) -> void {
    j.at("operations").get_to(bank.m_operations);
    j.at("users").get_to(bank.m_users);
  }
};
