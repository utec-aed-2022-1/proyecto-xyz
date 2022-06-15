#include <iostream>

#include "block.hpp"
#include "blockchain.hpp"
#include "catch.hpp"
#include "json.hpp"

using json = nlohmann::json;

TEST_CASE("blockchain", "[blockchain]") {
  Blockchain bs = blockchainFromFile("tests/json/blockchain1.json");

  auto const& bsv = bs.getBlocks();

  REQUIRE(
      bsv[0] ==
      Block{
          1, "Hello World", 9879,
          "0000000000000000000000000000000000000000000000000000000000000000",
          "0003D8C5719DD759F74C77AC1F32A6EBA6F202F081DDAF1DD9808D22AF8982AE"});
}
