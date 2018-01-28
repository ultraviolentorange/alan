#include "alan_brain.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

void start(const char* ciphertext, const char* dictionary_file, const char* outfile, const char* logfile,
const char* encryption_method, const char* displayed_top) {
	
	const bool dictionary_file_specified = strlen(dictionary_file) > 0;
	const bool outfile_specified = strlen(outfile) > 0;
	const bool logfile_specified = strlen(logfile) > 0;
	const bool encryption_method_specified = strlen(encryption_method) > 0;
	const bool displayed_top_specified = strlen(displayed_top) > 0;

	printf("\033[2J\033[1;1H");
	std::ifstream ascii_art_file("ascii_art.txt");
	std::string art_line;
	for (; getline(ascii_art_file, art_line); ) {
		printf("%s\n", art_line.c_str());
	} 

	printf("\nStarting alan v1.0...\n[Settings]\n");
	
	printf("Dictionary file:   ");
	if (dictionary_file_specified) {
		printf("%s\n", dictionary_file);
	} else {
		dictionary_file = "rockyou.txt";
		printf("default (rockyou.txt)\n");
	}

	printf("Outfile:           ");
	if (outfile_specified) {
		printf("%s\n", outfile);
	} else {
		printf("default (stdout)\n");
	}

	printf("Logfile:           ");
	if (logfile_specified) {
		printf("%s\n", logfile);
	} else {
		printf("none\n");
	}

	printf("Encryption method: ");
	if (encryption_method_specified) {
		printf("%s\n", encryption_method);
	} else {
		printf("unknown\n");
	}

	printf("Displayed top:     ");
	if (displayed_top_specified) {
		printf("%s\n", displayed_top);
	} else {
		printf("default (100)\n");
	}

	if (!encryption_method_specified || strcmp(encryption_method, "caesar")) {
		run_caesar(ciphertext, logfile);
	}
}
