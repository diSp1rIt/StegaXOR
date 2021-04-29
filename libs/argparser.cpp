#include "argparser.h"


string key_file;
string text;
string output_file;
string input_file;


static unsigned int index = 0;


static bool findflag(int argc, const char * argv[], string flag) {
	for (int i = 0; i < argc; i++) {
		if (flag == argv[i]) {
			index = i;
			return true;
		}
	}
	return false;
}


Mode parse(int argc, const char * argv[]) {
	switch (argc) {
		case 2:
			if (findflag(argc, argv, string("-g")))
				return GENERATE;
			else
				return ERROR;
		case 6:
			if (findflag(argc, argv, string("-c"))) {
				if (findflag(argc, argv, string("-t")))
					text = string(argv[index + 1]);
				else
					return ERROR;

				if (findflag(argc, argv, string("-o")))
					output_file = string(argv[index + 1]);
				else
					return ERROR;
				return ENCRYPT;
			} else if (findflag(argc, argv, string("-d"))) {
				if (findflag(argc, argv, string("-i")))
					input_file = string(argv[index + 1]);
				else
					return ERROR;

				if (findflag(argc, argv, string("-o")))
					output_file = string(argv[index + 1]);
				else
					return ERROR;
				return DECRYPT;
			} else {
				return ERROR;
			}
		default:
			return ERROR;
	}
}
