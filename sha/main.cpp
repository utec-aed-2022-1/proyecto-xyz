#include <iostream>
#include "SHA256.h"

using namespace std;

int main() {
	string s = "hello world";
	SHA256 sha;
	sha.update(s);
	uint8_t * digest = sha.digest();

	cout << SHA256::toString(digest) << endl;

	delete[] digest;
}
