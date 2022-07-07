#include <stdio.h>

#include <cassert>
#include <stdexcept>
#include <string>

#include "bank.hpp"
#include "bank_operations.hpp"
#include "httplib.h"
#include "json.hpp"
#include "prettyprint.hpp"
#include "util.hpp"

using nlohmann::json;

auto main() -> int {
  using namespace httplib;

  Server svr;

  // bank.addUser(User{"1", "name1", "pass1"});
  // bank.addUser(User{"2", "name2", "pass2"});
  std::string const bank_file = "bank.json";
  Bank bank;

  // bank.pushOperation(BankTransfer{1, "id_user 1", 111, "date 1", "id_sender 1",
  //                                 "id_receiver 1"});
  // bank.pushOperation(
  //     BankWithdrawal{2, "id_user 2", 222, "date 2", "id_client 2"});
  // bank.pushOperation(BankSaleRegister{3, "id_user 3", 333, "date 3",
  //                                     "id_client 3", "id_seller 3"});

  svr.set_pre_routing_handler([](const auto& req, auto& res) {
    res.set_header("Access-Control-Allow-Headers", "*");
    res.set_header("Access-Control-Allow-Origin", "*");
    if (req.method == "OPTIONS") {
      return Server::HandlerResponse::Handled;
    }
    return Server::HandlerResponse::Unhandled;
  });

  svr.set_post_routing_handler([](const auto& req, auto& res) {
    std::cerr << "[" << req.method << "] " << req.path << " " << res.body
              << "\n";
  });

  svr.Get("/users", [&bank](const Request& /*req*/, Response& res) {
    res.set_content(json{bank.getUsers()}.dump(), "application/json");
  });

  svr.Get(R"(/user/(\d+))", [&](const Request& req, Response& res) {
    std::string const& id = req.matches[1];
    res.set_content(json{bank.getUser(id)}.dump(), "application/json");
  });

  svr.Post("/user", [&](const Request& /*req*/, Response& /*res*/,
                        const ContentReader& content_reader) {
    content_reader([&](const char* data, size_t /*data_length*/) {
      bank.addUser(json::parse(data).get<User>());
      return true;
    });
  });

  svr.Get("/operations", [&bank](const Request& /*req*/, Response& res) {
    res.set_content(json(bank.getOperations()).dump(), "application/json");
  });

  svr.Get("/operations/search", [&](const Request& req, Response& res) {
    auto const& params = req.params;

    if (auto type_it = params.find("type"); type_it != params.end()) {
      res.set_content(json(bank.searchByType(type_it->second)).dump(),
                      "application/json");
    } else if (auto id_user_it = params.find("id_user");
               id_user_it != params.end()) {
      res.set_content(json(bank.searchByIdUser(id_user_it->second)).dump(),
                      "application/json");
    } else if (auto id_amount_it = params.find("amount");
               id_amount_it != params.end()) {
      throw std::runtime_error("Not implemented");
    } else if (auto id_date_it = params.find("date");
               id_date_it != params.end()) {
      throw std::runtime_error("Not implemented");
    } else if (auto id_client_it = params.find("id_client");
               id_client_it != params.end()) {
      res.set_content(json(bank.searchByIdClient(id_client_it->second)).dump(),
                      "application/json");
    } else if (auto id_sender_it = params.find("id_sender");
               id_sender_it != params.end()) {
      res.set_content(json(bank.searchByIdSender(id_sender_it->second)).dump(),
                      "application/json");
    } else if (auto id_receiver_it = params.find("id_receiver");
               id_receiver_it != params.end()) {
      res.set_content(
          json(bank.searchByIdReceiver(id_receiver_it->second)).dump(),
          "application/json");
    } else if (auto id_seller_it = params.find("id_seller");
               id_seller_it != params.end()) {
      res.set_content(json(bank.searchByIdSeller(id_seller_it->second)).dump(),
                      "application/json");
    } else {
      throw std::runtime_error("Not implemented");
    }
  });

  svr.Post("/operation", [&](const Request& /*req*/, Response& /*res*/,
                             const ContentReader& content_reader) {
    content_reader([&](const char* data, size_t /*data_length*/) {
      json j = json::parse(data);
      j["id"] = 0;
      bank.pushOperation(j.get<BankOperation>());
      return true;
    });
  });

  svr.Get("/write", [&](const Request& /*req*/, Response& /*res*/) {
    jsonToFile(bank_file, json(bank));
  });

  size_t const port = 8000;
  std::cerr << "Listening on port " << port << "\n";
  svr.listen("localhost", port);
}
