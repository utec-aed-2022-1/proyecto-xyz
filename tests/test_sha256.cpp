#include <cstdint>
#include <vector>

#include "catch.hpp"
#include "sha256.hpp"

TEST_CASE("right rotate", "[sha256]") {
  CHECK(right_rotate(uint8_t(1), 1) == 0x80);
  CHECK(right_rotate(uint16_t(1), 1) == 0x8000);
  CHECK(right_rotate(uint32_t(1), 1) == 0x80000000);
  CHECK(right_rotate(uint64_t(1), 1) == 0x8000000000000000);
}

TEST_CASE("change_endianess", "[sha256]") {
  REQUIRE(change_endianess(0x11121314U) == 0x14131211U);
}

TEST_CASE("to hex", "[sha256]") {
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

  std::array<uint32_t, 8> v1 = {0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924,
                                0x27ae41e4, 0x649b934c, 0xa495991b, 0x7852b855};

  CHECK(to_hex_string(v1.begin(), v1.end()) ==
        "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");
}

TEST_CASE("sha256", "[sha256]") {
  CHECK(sha256_hex(std::vector<bool>()) ==
        "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");

  CHECK(
      // == "hello"
      sha256_hex(std::vector<bool>{0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1,
                                   0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0,
                                   1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1}) ==
      "2CF24DBA5FB0A30E26E83B2AC5B9E29E1B161E5C1FA7425E73043362938B9824");

  CHECK(
      // == 128
      sha256_hex(std::vector<bool>{1, 0, 0, 0, 0, 0, 0, 0}) ==
      "76BE8B528D0075F7AAE98D6FA57A6D3C83AE480A8469E668D7B0AF968995AC71");

  CHECK(
      // == 128
      sha256_hex(int(128)) ==
      "6D58692645C9D1CFAF13541CBD258F86193EF63C2F1D38F6BBCA9617372D7BD6");
}

TEST_CASE("sha256 integers", "[sha256]") {
  CHECK(to_hex_string(sha256(uint32_t{0xFFFFFFFF})) ==
        "AD95131BC0B799C0B1AF477FB14FCF26A6A9F76079E48BF090ACB7E8367BFD0E");

  CHECK(to_hex_string(sha256(uint32_t{0xAAAAAAAA})) ==
        "DBED14CEB001D110D766B9013D3B5BBFFAD6915475A9BA07932D2AC057944C04");

  CHECK(to_hex_string(sha256(uint32_t{0x11121314})) ==
        "1AA2454E38E78FBE098BE157EE8112D85D6E667E2304FDE4220850FAA2F46341");

  CHECK(to_hex_string(sha256(uint64_t{0xFF})) ==
        "B8862208A16D307A1E2B3A5DF2B44A63126BBA7CD20C985C436135AD88D2C735");
}

TEST_CASE("sha256 strings", "[sha256]") {
  using namespace std::string_literals;

  CHECK(sha256_hex("hello"s) ==
        "2CF24DBA5FB0A30E26E83B2AC5B9E29E1B161E5C1FA7425E73043362938B9824");

  CHECK(
      sha256_hex(
          "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam volutpat eleifend sem, in facilisis massa fermentum quis. Etiam efficitur nulla ac nulla tempus lobortis. Duis mattis vulputate libero quis interdum. Proin eleifend dignissim mi ut pretium. Nunc congue congue ex, vel pretium leo faucibus non. Integer accumsan quam sit amet velit tristique, et vestibulum massa molestie. Nulla facilisi. Aliquam eleifend augue eget viverra bibendum. Fusce ornare sed lectus eget egestas. Duis porttitor urna id lacinia dictum. Ut sed lectus efficitur, hendrerit metus in, venenatis purus.  Aliquam justo erat, fermentum id placerat non, pharetra auctor purus. Vestibulum pharetra tincidunt nulla eu iaculis. In sollicitudin arcu eu suscipit luctus. Vivamus aliquet placerat ipsum, sed sagittis est maximus nec. Proin eu ante augue. Pellentesque volutpat vehicula viverra. Cras dui dui, consectetur nec erat sed, condimentum lacinia nunc. Phasellus vehicula enim vitae mi lobortis congue. Duis eu blandit mauris.  Nulla facilisi. Nunc at auctor sem, quis pulvinar turpis. Donec in lacinia tortor, et vestibulum eros. Vestibulum tortor tellus, eleifend quis pulvinar eu, fermentum varius magna. In commodo odio orci, vestibulum molestie odio tristique at. Nam dignissim purus in purus pulvinar, eu malesuada velit ullamcorper. Nullam nec elit sed diam accumsan congue ut sed ipsum. Fusce auctor turpis ac nisl semper, vitae sollicitudin ligula aliquet. Nam eget odio sed libero vehicula faucibus. Maecenas malesuada mattis justo, nec rhoncus ex ullamcorper sit amet. Fusce dignissim a ligula ut facilisis.  Nam ac sapien a sem tempor faucibus eget id massa. Curabitur a ante ex. Phasellus venenatis mollis eros quis fermentum. Vivamus a mattis diam, ut sodales ligula. Nulla sagittis, arcu sed fermentum molestie, nisl urna commodo ex, eget eleifend mauris felis eu turpis. Duis nec nulla sit amet diam congue accumsan. Vestibulum fringilla urna vitae ornare luctus. Donec eget odio efficitur, volutpat nisi sit amet, convallis lorem. Pellentesque erat lorem, placerat vestibulum ex nec, viverra consequat mi. Mauris congue condimentum lacus, sit amet congue diam pretium ut.  Mauris feugiat posuere fringilla. Cras rutrum ultricies arcu, vitae elementum sem varius quis. Integer et enim odio. Praesent egestas pulvinar neque nec ultrices. Etiam ultricies nisi vitae tempor porttitor. Vivamus aliquam finibus leo imperdiet tristique. Ut non magna suscipit felis vestibulum laoreet. Phasellus eu turpis dui. Morbi ultricies risus quis dolor placerat, id consequat orci vulputate. Cras varius, turpis vitae tempus viverra, nunc mauris pharetra ex, eu efficitur tortor justo vitae purus."s) ==
      "4526444E57E84CA4D3EB63DE186F3D86CC19911550F3DB26106518FD4274E3BC");
}
