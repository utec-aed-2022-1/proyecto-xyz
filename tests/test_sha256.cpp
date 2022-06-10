#include <cstdint>
#include <vector>

#include "catch.hpp"
#include "sha256.hpp"

TEST_CASE("right rotate", "[sha256]")
{
    CHECK(right_rotate(uint8_t(1), 1) == 0x80);
    CHECK(right_rotate(uint16_t(1), 1) == 0x8000);
    CHECK(right_rotate(uint32_t(1), 1) == 0x80000000);
    CHECK(right_rotate(uint64_t(1), 1) == 0x8000000000000000);
}

TEST_CASE("change_endianess", "[sha256]")
{
    REQUIRE(change_endianess(0x11121314U) == 0x14131211U);
}

TEST_CASE("to hex", "[sha256]")
{
    CHECK(to_hex_string(1) == "00000001");
    CHECK(to_hex_string(1 << 4) == "00000010");
    CHECK(to_hex_string(1 << 8) == "00000100");
    CHECK(to_hex_string(1 << 12) == "00001000");
    CHECK(to_hex_string(1 << 16) == "00010000");
    CHECK(to_hex_string(1 << 20) == "00100000");
    CHECK(to_hex_string(1 << 24) == "01000000");
    CHECK(to_hex_string(1 << 28) == "10000000");

    CHECK(to_hex_string(10) == "0000000A");
    CHECK(to_hex_string(15) == "0000000F");

    std::array<uint32_t, 8> v1 = {
        0xe3b0c442,
        0x98fc1c14,
        0x9afbf4c8,
        0x996fb924,
        0x27ae41e4,
        0x649b934c,
        0xa495991b,
        0x7852b855};

    CHECK(
        to_hex_string(v1.begin(), v1.end())
        == "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");
}

TEST_CASE("sha256", "[sha256]")
{
    CHECK(
        sha256_hex(std::vector<bool>())
        == "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");

    CHECK(
        // == "hello"
        sha256_hex(std::vector<bool>{0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1,
                                     0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0,
                                     1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1})
        == "2CF24DBA5FB0A30E26E83B2AC5B9E29E1B161E5C1FA7425E73043362938B9824");

    CHECK(
        // == 128
        sha256_hex(std::vector<bool>{1, 0, 0, 0, 0, 0, 0, 0})
        == "76BE8B528D0075F7AAE98D6FA57A6D3C83AE480A8469E668D7B0AF968995AC71");

    CHECK(
        // == 128
        sha256_hex(int(128))
        == "6D58692645C9D1CFAF13541CBD258F86193EF63C2F1D38F6BBCA9617372D7BD6");
}
