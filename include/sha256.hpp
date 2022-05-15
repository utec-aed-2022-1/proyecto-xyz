#pragma once

#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
#include <deque>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

template<
    typename Integer,
    std::enable_if_t<std::numeric_limits<Integer>::is_integer, bool> = true>
auto right_rotate(Integer n, unsigned rotation) -> Integer
{
    constexpr unsigned integer_bits = sizeof(Integer) * CHAR_BIT;
    return n >> rotation | n << (integer_bits - rotation);
}

template<typename T>
auto sha256(T) -> std::array<uint32_t, 8>;

auto sha256(std::deque<bool> bytes) -> std::array<uint32_t, 8>;

auto to_hex_string(uint32_t n) -> std::string;
auto to_hex_string(std::bitset<4> n) -> std::string;

template<typename ForwardIterator>
auto to_hex_string(ForwardIterator b, ForwardIterator e) -> std::string
{
    std::ostringstream oss;

    while (b != e)
    {
        oss << to_hex_string(*b);

        ++b;
    }

    return oss.str();
}

template<typename... Args>
auto sha256_hex(Args... args) -> std::string
{
    auto arr = sha256(args...);
    return to_hex_string(arr.begin(), arr.end());
}
