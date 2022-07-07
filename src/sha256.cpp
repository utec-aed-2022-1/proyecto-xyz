#include "sha256.hpp"

#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// All 3 variants sourced from:
// https://github.com/HowardHinnant/hash_append/issues/7#issuecomment-629414712

auto hash_combine(uint16_t lhs, uint16_t rhs) -> size_t {
  lhs ^= rhs + 0x9e37U + (lhs << 3) + (lhs >> 1);
  return lhs;
}

auto hash_combine(uint32_t lhs, uint32_t rhs) -> size_t {
  lhs ^= rhs + 0x9e3779b9U + (lhs << 6) + (lhs >> 2);
  return lhs;
}

auto hash_combine(uint64_t lhs, uint64_t rhs) -> size_t {
  lhs ^= rhs + 0x9e3779b97f4a7c15 + (lhs << 12) + (lhs >> 4);
  return lhs;
}

/**
 * `lhs` is received by value to allow calling the move constructor in case the
 * argument is an rvalue and avoid allocating a new `std::array`.
 **/
auto hash_combine(std::array<uint32_t, 8> lhs,
                  std::array<uint32_t, 8> const& rhs)
    -> std::array<uint32_t, 8> {
  for (size_t i = 0; i < lhs.size(); ++i) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    lhs[i] = hash_combine(lhs[i], rhs[i]);
  }
  return lhs;
}

auto pre_process(std::vector<bool> bits) -> std::vector<bool> {
  uint64_t bits_original_size = bits.size();  // We asumme big endian

  bits.push_back(true);

  size_t bits_to_append = 512 - ((bits.size() + 64) % 512);
  for (size_t i = 0; i < bits_to_append; i++) {
    bits.push_back(false);
  }

  for (size_t i = 0; i < 64; i++) {
    bits.push_back(bits_original_size >> 63 == 1);

    bits_original_size <<= 1;
  }

  return bits;
}

auto sha256(std::vector<bool> bits) -> std::array<uint32_t, 8> {
  uint32_t h0 = 0x6a09e667;
  uint32_t h1 = 0xbb67ae85;
  uint32_t h2 = 0x3c6ef372;
  uint32_t h3 = 0xa54ff53a;
  uint32_t h4 = 0x510e527f;
  uint32_t h5 = 0x9b05688c;
  uint32_t h6 = 0x1f83d9ab;
  uint32_t h7 = 0x5be0cd19;

  std::array<uint32_t, 64> const round_constants = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
      0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
      0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
      0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
      0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

  bits = pre_process(bits);
  std::vector<bool>::size_type bits_i = 0;

  while (bits_i != bits.size()) {
    std::array<uint32_t, 64> w{};

    // 512 bits are processed each time around
    for (size_t i = 0; i < 16; i++) {
      uint32_t to_add = 0;
      for (size_t j = 0; j < 32; j++) {
        to_add = (to_add << 1) + bits[bits_i];
        ++bits_i;
      }
      w.at(i) = to_add;
    }

    for (size_t i = 16; i < 64; i++) {
      uint32_t s0 = right_rotate(w.at(i - 15), 7) ^
                    right_rotate(w.at(i - 15), 18) ^ (w.at(i - 15) >> 3);

      uint32_t s1 = right_rotate(w.at(i - 2), 17) ^
                    right_rotate(w.at(i - 2), 19) ^ (w.at(i - 2) >> 10);

      w.at(i) = w.at(i - 16) + s0 + w.at(i - 7) + s1;
    }

    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;
    uint32_t f = h5;
    uint32_t g = h6;
    uint32_t h = h7;

    for (unsigned i = 0; i < 64; i++) {
      uint32_t s1 =
          right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
      uint32_t ch = (e & f) ^ ((~e) & g);
      uint32_t temp1 = h + s1 + ch + round_constants.at(i) + w.at(i);

      uint32_t s0 =
          right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
      uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
      uint32_t temp2 = s0 + maj;

      h = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }

    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;
  }

  return {h0, h1, h2, h3, h4, h5, h6, h7};
}

auto sha256(uint8_t const* octets, uint64_t n_octets)
    -> std::array<uint32_t, 8> {
  uint32_t h0 = 0x6a09e667;
  uint32_t h1 = 0xbb67ae85;
  uint32_t h2 = 0x3c6ef372;
  uint32_t h3 = 0xa54ff53a;
  uint32_t h4 = 0x510e527f;
  uint32_t h5 = 0x9b05688c;
  uint32_t h6 = 0x1f83d9ab;
  uint32_t h7 = 0x5be0cd19;

  static constexpr std::array<uint32_t, 64> round_constants = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
      0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
      0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
      0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
      0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

  // 512 bits are processed each time around
  auto process_512 = [&](auto const& w_given) {
    std::array<uint32_t, 48> w_calc{};

    auto w = [&](size_t index) {
      if (index < 16) {
        return w_given(index);
      } else {
        return w_calc.at(index - 16);
      }
    };

    for (size_t i = 16; i < 64; i++) {
      uint32_t s0 = right_rotate(w(i - 15), 7) ^ right_rotate(w(i - 15), 18) ^
                    (w(i - 15) >> 3);

      uint32_t s1 = right_rotate(w(i - 2), 17) ^ right_rotate(w(i - 2), 19) ^
                    (w(i - 2) >> 10);

      w_calc.at(i - 16) = w(i - 16) + s0 + w(i - 7) + s1;
    }

    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;
    uint32_t f = h5;
    uint32_t g = h6;
    uint32_t h = h7;

    for (unsigned i = 0; i < 64; i++) {
      uint32_t s1 =
          right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
      uint32_t ch = (e & f) ^ ((~e) & g);
      uint32_t temp1 = h + s1 + ch + round_constants.at(i) + w(i);

      uint32_t s0 =
          right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
      uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
      uint32_t temp2 = s0 + maj;

      h = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }

    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;
  };

  size_t message_block_size = [=]() {
    size_t size_without_padding = n_octets * 8 + 8 + 64;
    size_t m512 = size_without_padding % 512;
    if (m512 == 0) {
      return size_without_padding;
    } else {
      return size_without_padding + 512 - m512;
    }
  }();
  assert(message_block_size % 512 == 0);

  bool should_break = false;
  auto get_octet = [&](size_t index) {
    if (index < n_octets) {
      return octets[index];
    } else if (index == n_octets) {
      return uint8_t{0x80};
    }
    // The size is 64 bits long = 8 octets
    else if ((message_block_size / 8 - 8) <= index) {
      size_t size_index = index - (message_block_size / 8 - 8);
      if (size_index == 7) {
        should_break = true;
      }
      return static_cast<uint8_t>((n_octets * 8) >> (8 * (7 - size_index)));
    } else {
      return uint8_t(0);
    }
  };

  size_t octets_read = 0;
  while (!should_break) {
    auto get32 = [&](size_t index) {
      uint32_t octet1 = get_octet(index * 4 + octets_read);
      uint32_t octet2 = get_octet(index * 4 + octets_read + 1);
      uint32_t octet3 = get_octet(index * 4 + octets_read + 2);
      uint32_t octet4 = get_octet(index * 4 + octets_read + 3);

      return (octet1 << 24) | (octet2 << 16) | (octet3 << 8) | octet4;
    };

    process_512(get32);
    octets_read += 512 / 8;
  }

  return {h0, h1, h2, h3, h4, h5, h6, h7};
}

auto sha256(std::string const& str) -> std::array<uint32_t, 8> {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  return sha256(reinterpret_cast<uint8_t const*>(str.data()), str.size());
}

auto to_hex_string(uint32_t n) -> std::string {
  using bs = std::bitset<4>;
  return to_hex_string(bs(n >> 28)) + to_hex_string(bs(n >> 24)) +
         to_hex_string(bs(n >> 20)) + to_hex_string(bs(n >> 16)) +
         to_hex_string(bs(n >> 12)) + to_hex_string(bs(n >> 8)) +
         to_hex_string(bs(n >> 4)) + to_hex_string(bs(n));
}

auto to_hex_string(std::bitset<4> n) -> std::string {
  switch (n.to_ulong()) {
    case 0:
      return "0";
    case 1:
      return "1";
    case 2:
      return "2";
    case 3:
      return "3";
    case 4:
      return "4";
    case 5:
      return "5";
    case 6:
      return "6";
    case 7:
      return "7";
    case 8:
      return "8";
    case 9:
      return "9";
    case 10:
      return "A";
    case 11:
      return "B";
    case 12:
      return "C";
    case 13:
      return "D";
    case 14:
      return "E";
    case 15:
      return "F";
    default:
      throw std::runtime_error("Nonsense");
  }
}
