#include <iostream>

#include "sha256.hpp"
#include "block.hpp"

using namespace std;

auto main() -> int
{
    cout << "Hello, World!" << endl;

    block blck(1, "Hello World");

    cout << blck.getHash() << endl;
    cout << blck.getPrevHash() << endl;

    cout << blck.calculateHash() << endl;

    blck.toJson();

    return 0;
}
