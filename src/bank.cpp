#include "bank.hpp"

auto to_json(json& j, User const& p) -> void {
  j = json{{"dni", p.dni}, {"name", p.name}, {"password", p.password}};
}

auto from_json(json const& j, User& p) -> void {
  j.at("dni").get_to(p.dni);
  j.at("name").get_to(p.name);
  j.at("password").get_to(p.password);
}
