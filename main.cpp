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
extern char *data_bytes;


int main(int argc, char const *argv[]) {
	// switch (parse(argc, argv)) {
	// 	case GENERATE:
	// 		generate(string("xor.key"));
	// 		cout << "Key generated\n";
	// 		break;
	// 	case ENCRYPT:
	// 		encrypt_b2f(text.c_str(), text.size(), output_file, string("xor.key"));
	// 		cout << text.c_str() << endl;
	// 		cout << "Message encrypted\n";
	// 		break;
	// 	case DECRYPT:
	// 		decrypt_f2f(input_file, output_file, string("xor.key"));
	// 		cout << "Message decrypted\n";
	// 		break;
	// 	case ERROR:
	// 		cerr << "Error with parsing argument\n";
	// 		exit(-1);
	// }
	StegaXOR cryptor (string("xor.key"));
	char message[] = "Hello, world!";
	cout << "Message length: " << strlen(message) << endl;
	cryptor.encrypt_b2b(message, strlen(message));
	cout << "Encrypted length: " << cryptor.get_encrypted_len() << endl;
	cryptor.decrypt_b2b(cryptor.get_encrypted(), cryptor.get_encrypted_len());
	cout << "Decrypted length: " << cryptor.get_decrypted_len() << endl;
	cout << "Decrypted message: " << cryptor.get_decrypted() << endl;
	return 0;
}