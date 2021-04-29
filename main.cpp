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
	
	// StegaXOR cryptor1 (string("xor.key"));
	// StegaXOR cryptor2 (string("test.key"));
	// char message[] = "Hello, world!";
	// cout << "Message length: " << strlen(message) << endl;
	// cryptor1.encrypt_b2b(message, strlen(message));
	// cout << "Encrypted length: " << cryptor1.get_encrypted_len() << endl;
	// cryptor2.decrypt_b2b(cryptor1.get_encrypted(), cryptor1.get_encrypted_len());
	// cout << "Decrypted length: " << cryptor2.get_decrypted_len() << endl;
	// cout << "Decrypted message: " << cryptor2.get_decrypted() << endl;
	return 0;
}