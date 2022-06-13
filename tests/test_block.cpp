#include "block.hpp"
#include "catch.hpp"

TEST_CASE("block", "[block]") {
  Block b = blockFromFile("tests/json/block1.json");

  REQUIRE(
      b ==
      Block{
          1, "Hello World", 9879,
          "0000000000000000000000000000000000000000000000000000000000000000",
          "0003D8C5719DD759F74C77AC1F32A6EBA6F202F081DDAF1DD9808D22AF8982AE"});
}
