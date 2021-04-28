#include "keygen.h"


static random_device gen;


void generate(const string output_file) {
	ofstream output (output_file, ios_base::trunc);

	if (!output.is_open()) {
		cerr << "Can not open or create file" << endl;
		exit(-1);
	}

	char *key = new char [1024];

	for (short i = 0; i < 1024; i++) {
		key = gen();
	}

	output.write(key, 1024);
	output.close();
}
