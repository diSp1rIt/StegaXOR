#ifndef STEGAXOR_LIB_H
#define STEGAXOR_LIB_H

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstring>


using namespace std;


class StegaXOR {
public:
	StegaXOR(const string key_file);
	//~StegaXOR();

	void encrypt_b2b(const char *input, const unsigned int input_len);
	void decrypt_b2b(const char *input, const unsigned int input_len);
	char *get_encrypted();
	char *get_decrypted();
	unsigned int get_encrypted_len();
	unsigned int get_decrypted_len();
private:
	char *decrypted_bytes;
	unsigned int decrypted_len;
	char *encrypted_bytes;
	unsigned int encrypted_len;
	unsigned char *key;
	unsigned int key_length;
	unsigned int random_data_length;
	unsigned int shift;
	random_device gen;
};


#endif