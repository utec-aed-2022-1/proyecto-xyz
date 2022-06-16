#include <array>
#include <cassert>
#include <iostream>

#include "blockchain.hpp"
#include "bank.hpp"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

auto main() -> int { /*
  // from console
  Block blck(1, "Hello World");

  // cout << blck.getHash() << endl;
  // cout << blck.getPrevHash() << endl;

  cout << "Hash inicial (id y data): " << endl;
  cout << blck.calculateHash() << endl;

  cout << "Mina el bloque: " << endl;
  json jsxn = blck.mineBlock(3);

  blck.saveInJson("aa/file.json");*/

  // from json file (falta implementar cuando hay más de 1 registro)
  // Block blck("blocksInput/1.json");
  // cout << blck.calculateHash() << endl;

  // cout << "Mina el bloque: " << endl;
  // json jsxn = blck.mineBlock(3);

  Blockchain bs = blockchainFromFile("mainjson.json");
  vector<Block> xd;
  xd = {{1, "mauri", 680,
         "000000000000000000000000000000000000000000"
         "0000000000000000000000",
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BA"
         "E7B0337A372D9E36CCB510"},
        {2, "2dsfsdfsfsdfsdfsds", 476,
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BA"
         "E7B0337A372D9E36CCB510",
         "000E588B369C95B84C27508BB34DBDCC08C3889D81"
         "3EF5E416408E9A0F7E522F"}};
  assert(bs.getBlocks() == xd);
  bs.push("camila-prestamo: 50$");
  xd = {{1, "mauri", 680,
         "0000000000000000000000000000000000000000000000000000000000000000",
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BAE7B0337A372D9E36CCB510"},
        {2, "2dsfsdfsfsdfsdfsds", 476,
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BAE7B0337A372D9E36CCB510",
         "000E588B369C95B84C27508BB34DBDCC08C3889D813EF5E416408E9A0F7E522F"},
        {3, "camila-prestamo: 50$", 1283,
         "000E588B369C95B84C27508BB34DBDCC08C3889D813EF5E416408E9A0F7E522F",
         "00019E1549661BCF33425C23B3C47F0D275733D20B30681C931219BB9D97EF18"}};
  assert(bs.getBlocks() == xd);

  bs.push("jefferson-prestamo: 10000$");

  Block jef = bs.getBlocks().back();
  cout << jef << endl;
  //  {
  //   4, "jefferson-prestamo: 10000$", 2925,
  //   "00019E1549661BCF33425C23B3C47F0D275733D20B30681C931219BB9D97EF18",
  //   "00020C1E5C693D80F35D577A12CD7185A5700FAABDEBB78D9465A5EF0176B1A7"
  //};
  bs.push("maria-prestamo: 1240$");
  Block maria = bs.getBlocks().back();
  cout << maria << endl;
  //  {
  //   5, "maria-prestamo: 1240$", 1078,
  //   "00020C1E5C693D80F35D577A12CD7185A5700FAABDEBB78D9465A5EF0176B1A7",
  //   "00070737C2D76C6DD998053D7A90F591936419A8D3F4DD0B290B31AD8BCD6CE5"
  //};

  xd = {{1, "mauri", 680,
         "0000000000000000000000000000000000000000000000000000000000000000",
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BAE7B0337A372D9E36CCB510"},
        {2, "2dsfsdfsfsdfsdfsds", 476,
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BAE7B0337A372D9E36CCB510",
         "000E588B369C95B84C27508BB34DBDCC08C3889D813EF5E416408E9A0F7E522F"},
        {3, "camila-prestamo: 50$", 1283,
         "000E588B369C95B84C27508BB34DBDCC08C3889D813EF5E416408E9A0F7E522F",
         "00019E1549661BCF33425C23B3C47F0D275733D20B30681C931219BB9D97EF18"},
        {4, "jefferson-prestamo: 10000$", 2925,
         "00019E1549661BCF33425C23B3C47F0D275733D20B30681C931219BB9D97EF18",
         "00020C1E5C693D80F35D577A12CD7185A5700FAABDEBB78D9465A5EF0176B1A7"},
        {5, "maria-prestamo: 1240$", 1078,
         "00020C1E5C693D80F35D577A12CD7185A5700FAABDEBB78D9465A5EF0176B1A7",
         "00070737C2D76C6DD998053D7A90F591936419A8D3F4DD0B290B31AD8BCD6CE5"}};
  assert(bs.getBlocks() == xd);

  bs.edit(3, "itsme Mario aksdalda");
  xd = {{1, "mauri", 680,
         "0000000000000000000000000000000000000000000000000000000000000000",
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BAE7B0337A372D9E36CCB510"},
        {2, "2dsfsdfsfsdfsdfsds", 476,
         "000CCCFDD6901DEBE2DB5FF5DEBDBADB6A68EFB1BAE7B0337A372D9E36CCB510",
         "000E588B369C95B84C27508BB34DBDCC08C3889D813EF5E416408E9A0F7E522F"},
        {3, "camila-prestamo: 50$", 1283,
         "000E588B369C95B84C27508BB34DBDCC08C3889D813EF5E416408E9A0F7E522F",
         "00019E1549661BCF33425C23B3C47F0D275733D20B30681C931219BB9D97EF18"},
        {4, "itsme Mario aksdalda", 2814,
         "00019E1549661BCF33425C23B3C47F0D275733D20B30681C931219BB9D97EF18",
         "000DFC8C76FBF4838D14E1F86DF99D8ED99351BFE295DD57771FCAEC55E6D282"},
        {5, "maria-prestamo: 1240$", 1234,
         "000DFC8C76FBF4838D14E1F86DF99D8ED99351BFE295DD57771FCAEC55E6D282",
         "0005228EC7761DFFEE6725A9C2CB6DBE9C5B21E509DF9E797558F9EA0B2116CD"}};
  assert(bs.getBlocks() == xd);

  assert(bs.size() == 5);
  assert(bs.find(1) == "2dsfsdfsfsdfsdfsds");
  
  return 0;
}
