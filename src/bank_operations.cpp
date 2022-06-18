#include "bank_operations.hpp"

#include "json.hpp"

using nlohmann::json;

auto to_json(json& j, BankWithdrawal const& bw) -> void {
  j = json{{"type", "withdrawal"},
           {"id_user", bw.id_user},
           {"amount", bw.amount},
           {"date", bw.date},
           {"id_client", bw.id_client}};
}

auto from_json(const json& j, BankWithdrawal& bw) -> void {
  j.at("id_user").get_to(bw.id_user);
  j.at("amount").get_to(bw.amount);
  j.at("date").get_to(bw.date);
  j.at("id_client").get_to(bw.id_client);
}

auto to_json(json& j, BankTransfer const& bt) -> void {
  j = json{{"type", "transfer"},        {"id_user", bt.id_user},
           {"amount", bt.amount},       {"date", bt.date},
           {"id_sender", bt.id_sender}, {"id_receiver", bt.id_receiver}};
}

auto from_json(const json& j, BankTransfer& bt) -> void {
  j.at("id_user").get_to(bt.id_user);
  j.at("amount").get_to(bt.amount);
  j.at("date").get_to(bt.date);
  j.at("id_sender").get_to(bt.id_sender);
  j.at("id_receiver").get_to(bt.id_receiver);
}

auto to_json(json& j, BankSaleRegister const& bsr) -> void {
  j = json{{"type", "sale_register"},    {"id_user", bsr.id_user},
           {"amount", bsr.amount},       {"date", bsr.date},
           {"id_client", bsr.id_client}, {"id_seller", bsr.id_seller}};
}

auto from_json(const json& j, BankSaleRegister& bw) -> void {
  j.at("id_user").get_to(bw.id_user);
  j.at("amount").get_to(bw.amount);
  j.at("date").get_to(bw.date);
  j.at("id_client").get_to(bw.id_client);
  j.at("id_seller").get_to(bw.id_seller);
}
