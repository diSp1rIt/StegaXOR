#include <iostream>
#include <fstream>
#include <random>
#include <cstring>
#include <stdio.h>
#include "libs/stegaxor.h"
#include "libs/keygen.h"


using namespace std;


int main(int argc, char const *argv[]) {
	StegaXOR cryptor (string("xor.key"));
	cryptor.encrypt_f2f(string("makefile"), string("output"));
	cryptor.decrypt_f2f(string("output"), string("test.txt"));
	ifstream src ("makefile");
	ifstream res ("test.txt");
	char *buffer = new char[1024];
	src.read(buffer, 1024);
	cout << buffer << endl;
	res.read(buffer, 1024);
	cout << buffer << endl;
	return 0;
}