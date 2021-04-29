#include "stegaxor.h"


static unsigned int gcd(unsigned int a, unsigned int b) { 
	unsigned int t;
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}


// static unsigned int get_file_size(const string file) {
// 	ifstream file_;
// 	file_.open(file);
// 	file_.seekg(0, ios_base::end);
// 	unsigned int len = (unsigned int)file_.tellg();
// 	file_.close();
// 	return len;
// }


// void encrypt_b2f(const char *input, const unsigned int data_len, const string output_file, const string key_file) {
// 	load_key(key_file);

// 	ofstream output (output_file, ios_base::trunc);

// 	if (!output.is_open()) {
// 		cerr << "Can not open or create file" << endl;
// 		exit(-1);
// 	}

//     for (unsigned int i = data_len * 2; i < data_len * 3; i++) {
//     	if (gcd(i, key_length % i) == 1) {
//     		shift = key_length % i;
//     		random_data_length = i;
//     		break;
//     	}
//     }

//     cout << "Shift: " << shift << endl;
//     cout << "Random length: " << random_data_length << endl;

//     char byte;

//     for (unsigned int i = 0; i < random_data_length; i++) {
//     	byte = gen() % 256;
//     	output.write(&byte, 1);
//     }

//     unsigned int data_index = 0;
//     unsigned int key_index = 0;
    
//     for (unsigned int i = 0; i < data_len; i++) {
//     	byte = input[i] ^ key[key_index];
//     	output.seekp(data_index, ios_base::beg);
//     	output.write(&byte, 1);
//     	data_index = (data_index + shift) % random_data_length;
//     	key_index = (key_index + 1) % key_length;
//     }

//     byte = '\0' ^ key[key_index];
//     output.seekp(data_index, ios_base::beg);
//     output.write(&byte, 1);

// 	if (output.is_open())
// 		output.close();
// }


// void decrypt_f2f(const string input_file, const string output_file, const string key_file) {
// 	unsigned int data_len = get_file_size(input_file);
// 	char *data_bytes = new char [data_len];
// 	char *decrypted_bytes = new char [data_len];
// 	unsigned int decrypted_len = 0; 

// 	ifstream input (input_file);
// 	ofstream output (output_file, ios_base::trunc);

// 	if (!input.is_open()) {
// 		cerr << "Can not open file" << endl;
// 		exit(-1);
// 	}

// 	if (!output.is_open()) {
// 		cerr << "Can not open or create file" << endl;
// 		exit(-1);
// 	}

// 	load_key(key_file);

// 	input.read(data_bytes, data_len);

// 	unsigned int shift = key_length % data_len; 

// 	unsigned int i = 0;
// 	unsigned int data_index = 0;
//     unsigned int key_index = 0;

//     cout << "Shift: " << shift << endl;
//     cout << "Random length: " << data_len << endl;

// 	while (true) {
//     	decrypted_bytes[i] = data_bytes[data_index] ^ key[key_index];
//     	data_index = (data_index + shift) % data_len;
//     	key_index = (key_index + 1) % key_length;
//     	if (decrypted_bytes[i] == '\0') {
//     		decrypted_len = i;
//     		break;
//     	}
//     	i++;
//     }

//     output.write(decrypted_bytes, decrypted_len);

// 	if (input.is_open())
// 		input.close();
// 	if (output.is_open())
// 		output.close();
// }


StegaXOR::StegaXOR(const string key_file) {
	this->random_data_length = 0;
	this->shift = 0;
	this->key = new unsigned char [1024];
	this->key_length = 0;

	ifstream fd (key_file);

	if (!fd.is_open()) {
		cout << "[-] Error opening \"" << key_file << "\" to load key." << endl;
		cout << "Generation new key..." << endl;

		ofstream fd_ (key_file, ios_base::trunc);

		if (!fd_.is_open()) {
			cout << "[-] Error creating\"" << key_file << "\"" << endl;
			cout << "Generation new key..." << endl;
			exit(-1);
		}

		for (unsigned short i = 0; i < 1024; i++) {
			char byte = this->gen() % 256;
			this->key[i] = byte;
			fd_.write(&byte, 1);
		}
		fd_.close();
		this->key_length = 1024;
		cout << "Key generated" << endl;
	} else {
		for (int i = 0; i < 1024; i++) {
			char buffer;
			if (fd.eof()) {
				this->key_length = i + 1;
				break;
			} else {
				fd.read(&buffer, 1);
				this->key[i] = buffer;
			}
		}
		if (this->key_length == 0)
			this->key_length = 1024;

		fd.close();
	}	
}


void StegaXOR::encrypt_b2b(const char *input, const unsigned int input_len) {
	for (unsigned int i = input_len * 2; i < input_len * 3; i++) {
    	if (gcd(i, key_length % i) == 1) {
    		this->shift = key_length % i;
    		this->random_data_length = i;
    		break;
    	}
    }

    cout << "Shift: " << this->shift << endl;
    cout << "Random length: " << this->random_data_length << endl;

    this->encrypted_bytes = new char [this->random_data_length];

    for (unsigned int i = 0; i < this->random_data_length; i++) {
    	this->encrypted_bytes[i] = this->gen() % 256;
    }

    unsigned int data_index = 0;
    unsigned int key_index = 0;
    
    for (unsigned int i = 0; i < input_len; i++) {
    	this->encrypted_bytes[data_index] = input[i] ^ this->key[key_index];
    	data_index = (data_index + this->shift) % this->random_data_length;
    	key_index = (key_index + 1) % this->key_length;
    }

    this->encrypted_bytes[data_index] = '\0' ^ this->key[key_index];
    this->encrypted_len = this->random_data_length;
}


void StegaXOR::decrypt_b2b(const char *input, const unsigned int input_len) {
	this->shift = this->key_length % input_len; 

	unsigned int i = 0;
	unsigned int data_index = 0;
    unsigned int key_index = 0;

    cout << "Shift: " << this->shift << endl;
    cout << "Random length: " << input_len << endl;

    this->decrypted_bytes = new char [input_len];

	while (true) {
    	this->decrypted_bytes[i] = input[data_index] ^ this->key[key_index];
    	data_index = (data_index + this->shift) % input_len;
    	key_index = (key_index + 1) % this->key_length;
    	if (this->decrypted_bytes[i] == '\0') {
    		this->decrypted_len = i;
    		break;
    	}
    	i++;
    }
}


char *StegaXOR::get_encrypted() {
	return this->encrypted_bytes;
}


char *StegaXOR::get_decrypted() {
	return this->decrypted_bytes;
}


unsigned int StegaXOR::get_encrypted_len() {
	return this->encrypted_len;
}


unsigned int StegaXOR::get_decrypted_len() {
	return this->decrypted_len;
}