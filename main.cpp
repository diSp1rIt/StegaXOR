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
	StegaXOR cryptor (string("makefile"));
	cryptor.encrypt_f2f(string("test_test.txt"), string("output"));
	cryptor.decrypt_f2f(string("output"), string("test.txt"));
	return 0;
}