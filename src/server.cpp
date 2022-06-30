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

  bank.pushOperation(
      BankTransfer{"id_user 1", 111, "date 1", "id_sender 1", "id_receiver 1"});
  bank.pushOperation(BankWithdrawal{"id_user 2", 222, "date 2", "id_client 2"});

  std::cerr << json{bank.getUsers()} << "\n";

  svr.Get("/users", [&bank](const Request& /*req*/, Response& res) {
    res.set_content(json{bank.getUsers()}.dump(), "text/json");
  });

  svr.Get(R"(/users/(\d+))", [&](const Request& req, Response& res) {
    std::string const& id = req.matches[1];
    res.set_content(json{bank.getUser(id)}.dump(), "text/json");
  });

  svr.Post("/users", [&](const Request& /*req*/, Response& /*res*/,
                         const ContentReader& content_reader) {
    content_reader([&](const char* data, size_t /*data_length*/) {
      bank.addUser(json::parse(data).get<User>());
      return true;
    });
  });

  svr.Get("/operations", [&bank](const Request& /*req*/, Response& res) {
    res.set_content(json(bank.getOperations()).dump(), "text/json");
  });

  svr.Post("/operations", [&](const Request& /*req*/, Response& /*res*/,
                              const ContentReader& content_reader) {
    content_reader([&](const char* data, size_t /*data_length*/) {
      bank.pushOperation(json::parse(data).get<BankOperation>());
      return true;
    });
  });

  size_t const port = 1234;
  svr.listen("localhost", port);
}