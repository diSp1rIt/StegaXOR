#include <iostream>
#include <fstream>
#include <random>
#include "libs/stegaxor.h"
#include "libs/keygen.h"


using namespace std;


void load_key(const string key_file);


int main(int argc, char const *argv[]) {
	if (argc != 2)
		exit(-1);

	generate(string("xor.key"));
    encrypt_data(argv[1], string("output"), string("xor.key"));
    decrypt_file(string("output"), string("dec.txt"), string("xor.key"));

	return 0;
}