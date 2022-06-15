//
// Created by Mauricio on 14/06/2022.
//

#ifndef PROYECTO_XYZ_BANK_H
#define PROYECTO_XYZ_BANK_H

struct User{
  size_t id;
  std::string dni;
  std::string name;
  std::string password;
};

void to_json(json& j, const User& p) {
  j = json{{"id", p.id}, {"dni", p.dni}, {"name", p.name},{"password", p.password}};
}

void from_json(const json& j, User& p) {
  j.at("id").get_to(p.id);
  j.at("dni").get_to(p.dni);
  j.at("name").get_to(p.name);
  j.at("password").get_to(p.password);
}

class bank{
 private:
  unordered_map<std::string,User> users;

 public:
  bank() = default;
  bool serialize(std::string filename);
};

bool bank::serialize(std::string filename){
  User usuario{1, "43414121", "Mauricio", "124sdadSAwa"};
  json j = usuario;
  cout<<j;
  //for(auto& x : this->users){
  //  json j = x.second;
  //}
  return true;
}

#endif  // PROYECTO_XYZ_BANK_H
