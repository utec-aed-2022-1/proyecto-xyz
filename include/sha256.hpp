#pragma once

#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

template <
    typename Integer,
    std::enable_if_t<std::numeric_limits<Integer>::is_integer, bool> = true>
auto right_rotate(Integer n, unsigned rotation) -> Integer {
  return n >> rotation | n << (std::numeric_limits<Integer>::digits - rotation);
}

template <
    typename Integer,
    std::enable_if_t<std::numeric_limits<Integer>::is_integer, bool> = true>
auto change_endianess(Integer n) -> Integer {
  static constexpr size_t n_digits =
      std::numeric_limits<Integer>::digits +
      (std::numeric_limits<Integer>::is_signed ? 1 : 0);
  ;
  Integer ret = 0;
  Integer byte_mask = 0xFF;
  for (size_t i = 0; i < n_digits; i += 8) {
    ret <<= 8;
    ret += byte_mask & (n >> i);
  }
  return ret;
}

auto sha256(std::vector<bool> bytes) -> std::array<uint32_t, 8>;
auto sha256(uint8_t const* octets, uint64_t n_octets)
    -> std::array<uint32_t, 8>;

template <typename T>
auto sha256_raw(T const& v) -> std::array<uint32_t, 8> {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  auto p8 = reinterpret_cast<uint8_t const*>(&v);
  return sha256(p8, sizeof(v));
}

template <
    typename Integer,
    std::enable_if_t<std::numeric_limits<Integer>::is_integer, bool> = true>
auto sha256(Integer n) -> std::array<uint32_t, 8> {
  return sha256_raw(change_endianess(n));
}

auto sha256(std::string const& str) -> std::array<uint32_t, 8>;

auto to_hex_string(uint32_t n) -> std::string;
auto to_hex_string(std::bitset<4> n) -> std::string;

template <typename ForwardIterator>
auto to_hex_string(ForwardIterator b, ForwardIterator e) -> std::string {
  std::ostringstream oss;

  while (b != e) {
    oss << to_hex_string(*b);

    ++b;
  }

  return oss.str();
}

template <
    typename Container,
    std::enable_if_t<std::is_same_v<typename Container::value_type, uint32_t>,
                     bool> = true>
auto to_hex_string(Container const& c) -> std::string {
  return to_hex_string(c.begin(), c.end());
}

template <typename... Args>
auto sha256_hex(Args... args) -> std::string {
  auto arr = sha256(args...);
  return to_hex_string(arr.begin(), arr.end());
}
