#include <array>
#include <iostream>

#include "sha256.hpp"
#include "block.hpp"

using namespace std;

auto main() -> int
{
    cout << "Hello, World!" << endl;

    block blck(1, "Hello World");

    // cout << blck.getHash() << endl;
    // cout << blck.getPrevHash() << endl;

    array<uint32_t, 8> aa = blck.calculateHash();

    cout << aa[0] << endl;

    // blck.toJson();

    return 0;
}
