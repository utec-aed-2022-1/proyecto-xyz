#include "bank.hpp"

auto to_json(json& j, User const& p) -> void {
  j = json{
      {"id", p.id}, {"dni", p.dni}, {"name", p.name}, {"password", p.password}};
}

auto from_json(json const& j, User& p) -> void {
  j.at("id").get_to(p.id);
  j.at("dni").get_to(p.dni);
  j.at("name").get_to(p.name);
  j.at("password").get_to(p.password);
}

auto Bank::serialize(string filepath) -> bool {
  User usuario{1, "43414121", "Mauricio", "124sdadSAwa"};
  ifstream fp{filepath};
  json j;
  fp >> j;

  to_json(j, usuario);
  // return j.get<Bank>();
  return true;
}

auto Bank::deserialize(json jsxn, string filepath) -> bool {
  User usuario{1, "43414121", "Mauricio", "124sdadSAwa"};
  from_json(jsxn, usuario);
  
  return true;
}