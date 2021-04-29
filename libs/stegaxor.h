#ifndef STEGAXOR_LIB_H
#define STEGAXOR_LIB_H

#include <iostream>
#include <fstream>
#include <random>
#include <string>


using namespace std;


void encrypt_b2f(const char *input, const unsigned int data_len, const string output_file, const string key_file);
void decrypt_f2f(const string input_file, const string output_file, const string key_file);


#endif