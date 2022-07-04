#pragma once

#include <cstddef>
#include <string>
#include <variant>

#include "json.hpp"

// All currency amounts are in cents (i.e., amount = 100 means 100 cents which
// means 1 of whatever currency)

struct BankWithdrawal {
  static const std::string type;

  size_t id;
  std::string id_user;
  size_t amount;
  std::string date;
  std::string id_client;
};

auto to_json(nlohmann::json& j, BankWithdrawal const& bw) -> void;
auto from_json(const nlohmann::json& j, BankWithdrawal& bw) -> void;

struct BankTransfer {
  static const std::string type;

  size_t id;
  std::string id_user;
  size_t amount;
  std::string date;
  std::string id_sender;
  std::string id_receiver;
};

auto to_json(nlohmann::json& j, BankTransfer const& bt) -> void;
auto from_json(const nlohmann::json& j, BankTransfer& bt) -> void;

struct BankSaleRegister {
  static const std::string type;

  size_t id;
  std::string id_user;
  size_t amount;
  std::string date;
  std::string id_client;
  std::string id_seller;
};

auto to_json(nlohmann::json& j, BankSaleRegister const& bsr) -> void;
auto from_json(const nlohmann::json& j, BankSaleRegister& bw) -> void;

using BankOperation =
    std::variant<BankWithdrawal, BankTransfer, BankSaleRegister>;

auto to_json(nlohmann::json& j, BankOperation const& bop) -> void;
auto from_json(const nlohmann::json& j, BankOperation& bop) -> void;
