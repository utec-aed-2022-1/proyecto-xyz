#include <stdio.h>

#include <cassert>
#include <stdexcept>
#include <string>

#include "bank.hpp"
#include "bank_operations.hpp"
#include "httplib.h"
#include "json.hpp"
#include "prettyprint.hpp"

using nlohmann::json;

auto main() -> int {
  using namespace httplib;

  Server svr;

  Bank bank;
  bank.addUser(User{"1", "name1", "pass1"});
  bank.addUser(User{"2", "name2", "pass2"});

  bank.pushOperation(BankTransfer{1, "id_user 1", 111, "date 1", "id_sender 1",
                                  "id_receiver 1"});
  bank.pushOperation(
      BankWithdrawal{2, "id_user 2", 222, "date 2", "id_client 2"});

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

  svr.Post("/user", [&](const Request& /*req*/, Response& res,
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
    } else {
      throw std::runtime_error("Not implemented");
    }
  });

  svr.Post("/operation", [&](const Request& /*req*/, Response& res,
                             const ContentReader& content_reader) {
    content_reader([&](const char* data, size_t /*data_length*/) {
      bank.pushOperation(json::parse(data).get<BankOperation>());
      return true;
    });
  });

  size_t const port = 8000;
  std::cerr << "Listening on port " << port << "\n";
  svr.listen("localhost", port);
}
