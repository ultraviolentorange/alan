#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "alan_brain.h"
#include "candidate_evaluator.h"
#include "cfg_handler.h"

const std::string INVALID_ARGUMENTS_MESSAGE = "Invalid arguments";
const std::string INVALID_CIPHERTEXT_MESSAGE = "Invalid ciphertext. Requirements: alphanumeric (a-zA-Z0-9), length < 256";

inline void exit_with_message(const std::string error_message) {
	std::cout << "Error occured: " << error_message << ".\n";
	exit(0);
}

inline void ensure(bool condition, const std::string error_message) {
	if (!condition) exit_with_message(error_message);		
}

inline bool is_valid_dictionary_file(const std::string dictionary_file) {
	if (dictionary_file.empty()) return true;

	return fopen(dictionary_file.c_str(), "r") != NULL;
}

inline bool is_valid_displayed_top(const std::string displayed_top) {
	if ((int)displayed_top.size() > 8) return false;

	for (int i = 0; i < (int)displayed_top.size(); i++) {
		if ('0' <= displayed_top[i] && displayed_top[i] <= '9') continue;
		return false;
	}

	return true;
}

inline bool is_valid_ciphertext(const std::string ciphertext) {
	if ((int)ciphertext.size() > 255) return false;

	for (int i = 0; i < (int)ciphertext.size(); i++) {
		if ('a' <= ciphertext[i] && ciphertext[i] <= 'z') continue;
		if ('A' <= ciphertext[i] && ciphertext[i] <= 'Z') continue;
		if ('0' <= ciphertext[i] && ciphertext[i] <= '9') continue;
		return false;
	}

	return true;
}

inline bool is_valid_encryption_method(const std::string encryption_method) {
	if (encryption_method.empty()) return true;

	if (encryption_method == "caesar") return true;
	if (encryption_method == "affine") return true;
	
	return false;
}

inline bool parse_argument(int argc, const char** argv, int& i, const char* full_specifier,
const char* shortened_specifier, std::string& argument_variable) {
	if (i >= argc) return false;
	if (strcmp(argv[i], full_specifier) == 0 || strcmp(argv[i], shortened_specifier) == 0) {
		ensure(i + 1 < argc, INVALID_ARGUMENTS_MESSAGE);
		argument_variable = (std::string)argv[i + 1];
		i += 2;
		return true;
	}
	return false;
}

int main(int argc, const char** argv) {
	ensure(argc % 2 == 0, INVALID_ARGUMENTS_MESSAGE);

	if (strcmp(argv[1], "--about") == 0 || strcmp(argv[1], "-A") == 0) {
		std::cout << "\033[2J\033[1;1H";
		std::ifstream ascii_art_file("ascii_art.txt");
		std::string art_line;
		for (; getline(ascii_art_file, art_line); ) {
			std::cout << art_line << "\n";
		}
		std::cout << "\n\n";
		std::ifstream about_file("about.txt");
		std::string about_line;
		for (; getline(about_file, about_line); ) {
			std::cout << about_line << "\n";
		}
		std::cout << "\n";
		exit(0); 
	}
	
	std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key;

	int i = 1;
	while (i < argc) {
		if (parse_argument(argc, argv, i, "--dictionary", "-D", dictionary_file)) continue;
		if (parse_argument(argc, argv, i, "--outfile", "-O", outfile)) continue;
		if (parse_argument(argc, argv, i, "--logfile", "-L", logfile)) continue;
		if (parse_argument(argc, argv, i, "--type", "-T", encryption_method)) continue;
		if (parse_argument(argc, argv, i, "--top", "-N", displayed_top)) continue;
		if (parse_argument(argc, argv, i, "--key", "-K", cipher_key)) continue;
		
		if (!ciphertext.empty()) ciphertext += " ";
		ciphertext += (std::string)argv[i];
		i++;
	}

	ensure(is_valid_dictionary_file(dictionary_file), INVALID_ARGUMENTS_MESSAGE);
	ensure(is_valid_encryption_method(encryption_method), INVALID_ARGUMENTS_MESSAGE);
	ensure(is_valid_displayed_top(displayed_top), INVALID_ARGUMENTS_MESSAGE);
	ensure(is_valid_ciphertext(ciphertext), INVALID_CIPHERTEXT_MESSAGE); 

	configure(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key);

	start();

	return 0;
}
