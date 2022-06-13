#include "block.hpp"
#include "catch.hpp"

TEST_CASE("block", "[block]") {
  Block b = blockFromFile("tests/json/block1.json");

  REQUIRE(b.data == "Hello World");
  REQUIRE(b.hash ==
          "0003D8C5719DD759F74C77AC1F32A6EBA6F202F081DDAF1DD9808D22AF8982AE");
  REQUIRE(b.id == 1);
  REQUIRE(b.nonce == 9879);
  REQUIRE(b.prevHash ==
          "0000000000000000000000000000000000000000000000000000000000000000");
}
