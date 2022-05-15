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

template<
    typename Integer,
    std::enable_if_t<std::numeric_limits<Integer>::is_integer, bool> = true>
auto right_rotate(Integer n, unsigned rotation) -> Integer
{
    return n >> rotation | n << (std::numeric_limits<Integer>::digits - rotation);
}

auto sha256(std::vector<bool> bytes) -> std::array<uint32_t, 8>;

template<
    typename Integer,
    std::enable_if_t<std::numeric_limits<Integer>::is_integer, bool> = true>
auto sha256(Integer n, bool strip_leading_zeroes = true) -> std::array<uint32_t, 8>
{
    std::vector<bool> integer_in_bits;
    int n_digits = std::numeric_limits<Integer>::digits;

    if (strip_leading_zeroes)
    {
        while (n_digits > 0)
        {
            if ((n >> (n_digits - 1)) & 1)
            {
                break;
            }
            --n_digits;
        }
    }

    while (n_digits > 0)
    {
        integer_in_bits.push_back(n >> (n_digits - 1) & 1);
        --n_digits;
    }

    return sha256(integer_in_bits);
}

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
