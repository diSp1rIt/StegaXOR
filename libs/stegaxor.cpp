#include "stegaxor.h"


static random_device gen;

static unsigned int random_data_length = 0;
static unsigned int shift = 0;

static unsigned char *key = new unsigned char [1024];
static unsigned int key_length = 0;


static void load_key(const string key_file) {
	ifstream fd (key_file);
	if (!fd.is_open()) {
		cout << "[-] Error opening \"" << key_file << "\" to load key." << endl;;
		cout << "Be sure the file exists." << endl;
		exit(-1);
	}

	for (int i = 0; i < 1024; i++) {
		char buffer;
		if (fd.eof()) {
			key_length = i + 1;
			break;
		} else {
			fd.read(&buffer, 1);
			key[i] = buffer;
		}
	}
	if (key_length == 0)
		key_length = 1024;

	fd.close();
}


static unsigned int gcd(unsigned int a, unsigned int b) { 
	unsigned int t;
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}


static unsigned int get_file_size(const string file) {
	ifstream file_;
	file_.open(file);
	file_.seekg(0, ios_base::end);
	unsigned int len = (unsigned int)file_.tellg();
	file_.close();
	return len;
}


void encrypt_data(const char *input, const unsigned int data_len, const string output_file, const string key_file) {
	load_key(key_file);

	ofstream output (output_file, ios_base::trunc);

	if (!output.is_open()) {
		cerr << "Can not open or create file" << endl;
		exit(-1);
	}

    for (unsigned int i = data_len * 2; i < data_len * 3; i++) {
    	if (gcd(i, key_length % i) == 1) {
    		shift = key_length % i;
    		random_data_length = i;
    		break;
    	}
    }

    cout << "Shift: " << shift << endl;
    cout << "Random length: " << random_data_length << endl;

    char byte;

    for (unsigned int i = 0; i < random_data_length; i++) {
    	byte = gen() % 256;
    	output.write(&byte, 1);
    }

    unsigned int data_index = 0;
    unsigned int key_index = 0;
    
    for (unsigned int i = 0; i < data_len; i++) {
    	byte = input[i] ^ key[key_index];
    	output.seekp(data_index, ios_base::beg);
    	output.write(&byte, 1);
    	data_index = (data_index + shift) % random_data_length;
    	key_index = (key_index + 1) % key_length;
    }

    byte = '\0' ^ key[key_index];
    output.seekp(data_index, ios_base::beg);
    output.write(&byte, 1);

	if (output.is_open())
		output.close();
}


void decrypt_file(const string input_file, const string output_file, const string key_file) {
	unsigned int data_len = get_file_size(input_file);
	char *data_bytes = new char [data_len];
	char *decrypted_bytes = new char [data_len];
	unsigned int decrypted_len = 0; 

	ifstream input (input_file);
	ofstream output (output_file, ios_base::trunc);

	if (!input.is_open()) {
		cerr << "Can not open file" << endl;
		exit(-1);
	}

	if (!output.is_open()) {
		cerr << "Can not open or create file" << endl;
		exit(-1);
	}

	load_key(key_file);

	input.read(data_bytes, data_len);

	unsigned int shift = key_length % data_len; 

	unsigned int i = 0;
	unsigned int data_index = 0;
    unsigned int key_index = 0;

    cout << "Shift: " << shift << endl;
    cout << "Random length: " << data_len << endl;

	while (true) {
    	decrypted_bytes[i] = data_bytes[data_index] ^ key[key_index];
    	data_index = (data_index + shift) % data_len;
    	key_index = (key_index + 1) % key_length;
    	if (decrypted_bytes[i] == '\0') {
    		decrypted_len = i;
    		break;
    	}
    	i++;
    }

    output.write(decrypted_bytes, decrypted_len);

	if (input.is_open())
		input.close();
	if (output.is_open())
		output.close();
}