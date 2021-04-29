#include <iostream>
#include <fstream>
#include <random>
#include <cstring>
#include <stdio.h>
#include "libs/stegaxor.h"
#include "libs/keygen.h"
#include "libs/argparser.h"


using namespace std;


extern string key_file;
extern string text;
extern string output_file;
extern string input_file;


int main(int argc, char const *argv[]) {
	switch (parse(argc, argv)) {
		case GENERATE:
			generate(string("xor.key"));
			cout << "Key generated\n";
			break;
		case ENCRYPT:
			encrypt_data(text.c_str(), text.size(), output_file, string("xor.key"));
			cout << text.c_str() << endl;
			cout << "Message encrypted\n";
			break;
		case DECRYPT:
			decrypt_file(input_file, output_file, string("xor.key"));
			cout << "Message decrypted\n";
			break;
		case ERROR:
			cerr << "Error with parsing argument\n";
			exit(-1);
	}
	return 0;
}