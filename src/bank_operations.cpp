#include "bank_operations.hpp"

#include <functional>
#include <stdexcept>
#include <variant>

#include "json.hpp"
#include "sha256.hpp"
#include "util.hpp"

using nlohmann::json;

const std::string BankWithdrawal::type = "withdrawal";

auto to_json(json& j, BankWithdrawal const& bw) -> void {
  j = json{{"id", bw.id},           {"type", BankWithdrawal::type},
           {"id_user", bw.id_user}, {"amount", bw.amount},
           {"date", bw.date},       {"id_client", bw.id_client}};
}

auto from_json(const json& j, BankWithdrawal& bw) -> void {
  j.at("id").get_to(bw.id);
  j.at("id_user").get_to(bw.id_user);
  j.at("amount").get_to(bw.amount);
  j.at("date").get_to(bw.date);
  j.at("id_client").get_to(bw.id_client);
}

auto sha256(BankWithdrawal const& bw) -> std::array<uint32_t, 8> {
  return sha256(bw.id, bw.id_user, bw.amount, bw.date, bw.id_client);
}

const std::string BankTransfer::type = "transfer";

auto to_json(json& j, BankTransfer const& bt) -> void {
  j = json{{"id", bt.id},
           {"type", BankTransfer::type},
           {"id_user", bt.id_user},
           {"amount", bt.amount},
           {"date", bt.date},
           {"id_sender", bt.id_sender},
           {"id_receiver", bt.id_receiver}};
}

auto from_json(const json& j, BankTransfer& bt) -> void {
  j.at("id").get_to(bt.id);
  j.at("id_user").get_to(bt.id_user);
  j.at("amount").get_to(bt.amount);
  j.at("date").get_to(bt.date);
  j.at("id_sender").get_to(bt.id_sender);
  j.at("id_receiver").get_to(bt.id_receiver);
}

auto sha256(BankTransfer const& bt) -> std::array<uint32_t, 8> {
  return sha256(bt.id, bt.id_user, bt.amount, bt.date, bt.id_sender,
                bt.id_receiver);
}

const std::string BankSaleRegister::type = "sale_register";

auto to_json(json& j, BankSaleRegister const& bsr) -> void {
  j = json{{"id", bsr.id},
           {"type", BankSaleRegister::type},
           {"id_user", bsr.id_user},
           {"amount", bsr.amount},
           {"date", bsr.date},
           {"id_client", bsr.id_client},
           {"id_seller", bsr.id_seller}};
}

auto from_json(const json& j, BankSaleRegister& bw) -> void {
  j.at("id").get_to(bw.id);
  j.at("id_user").get_to(bw.id_user);
  j.at("amount").get_to(bw.amount);
  j.at("date").get_to(bw.date);
  j.at("id_client").get_to(bw.id_client);
  j.at("id_seller").get_to(bw.id_seller);
}

auto sha256(BankSaleRegister const& bsr) -> std::array<uint32_t, 8> {
  return sha256(bsr.id, bsr.id_user, bsr.amount, bsr.date, bsr.id_client,
                bsr.id_seller);
}

auto to_json(json& j, BankOperation const& bop) -> void {
  std::visit([&j](auto const& sbop) { to_json(j, sbop); }, bop);
}

auto from_json(const json& j, BankOperation& bop) -> void {
  if (j["type"] == "withdrawal") {
    BankWithdrawal bo;
    from_json(j, bo);
    bop = bo;
  } else if (j["type"] == "transfer") {
    BankTransfer bo;
    from_json(j, bo);
    bop = bo;
  } else if (j["type"] == "sale_register") {
    BankSaleRegister bo;
    from_json(j, bo);
    bop = bo;
  } else {
    throw std::runtime_error("No recognized type");
  }
}

auto to_json(nlohmann::json& j, BankOperation const* bop) -> void {
  to_json(j, *bop);
}

auto get_type(BankOperation const& bop) -> std::string const& {
  return std::visit(overload{[](BankWithdrawal const&) -> std::string const& {
                               return BankWithdrawal::type;
                             },
                             [](BankTransfer const&) -> std::string const& {
                               return BankTransfer::type;
                             },
                             [](BankSaleRegister const&) -> std::string const& {
                               return BankSaleRegister::type;
                             }},
                    bop);
}
