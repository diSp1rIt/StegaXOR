#ifndef STEGAXOR_LIB_H
#define STEGAXOR_LIB_H

#include <iostream>
#include <fstream>
#include <random>


using namespace std;


void encrypt_data(const char *input, const string output_file, const string key_file);
void decrypt_file(const string input_file, const string output_file, const string key_file);


#endif