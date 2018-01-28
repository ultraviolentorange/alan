#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "alan_brain.h"

const char* UKNOWN_ENCRYPTION_METHOD_MESSAGE = "Unknown encryption method"; 
const char* INVALID_ARGUMENTS_MESSAGE = "Invalid arguments";
const char* INVALID_CIPHERTEXT_MESSAGE = "Invalid ciphertext. Requirements: alphanumeric (a-zA-Z0-9), length < 256";

inline void exit_with_message(const char* error_message) {
	printf("Error occured: %s.\n", error_message);
	exit(0);
}

inline void ensure(bool condition, const char* error_message) {
	if (!condition) {
		exit_with_message(error_message);		
	}
}

inline bool is_valid_dictionary_file(const char* dictionary_file) {
	if (!strlen(dictionary_file)) {
		return true;
	}
	return fopen(dictionary_file, "r") != NULL;
}

inline bool is_valid_displayed_top(const char* displayed_top) {
	if (strlen(displayed_top) > 8) {
		return false;
	}
	for (int i = 0; displayed_top[i]; i++) {
		if ('0' <= displayed_top[i] && displayed_top[i] <= '9') {
			continue;
		}
		return false;
	}
	return true;
}

inline bool is_valid_ciphertext(const char* ciphertext) {
	if (strlen(ciphertext) > 255) {
		return false;
	}
	for (int i = 0; ciphertext[i]; i++) {
		if ('a' <= ciphertext[i] && ciphertext[i] <= 'z') {
			continue;
		}
		if ('A' <= ciphertext[i] && ciphertext[i] <= 'Z') {
			continue;
		}
		if ('0' <= ciphertext[i] && ciphertext[i] <= '9') {
			continue;
		}
		return false;
	}
	return true;
}

inline bool is_valid_encryption_method(const char* encryption_method) {
	if (!strlen(encryption_method)) {
		return true;
	}
	if (strcmp(encryption_method, "caesar") == 0) {
		return true;
	}
	if (strcmp(encryption_method, "affine") == 0) {
		return true;
	}
	return false;
}

inline bool parse_argument(int argc, const char** argv, int& i, const char* full_specifier,
const char* shortened_specifier, char* argument_variable) {
	if (i >= argc) {
		return false;
	}
	if (strcmp(argv[i], full_specifier) == 0 || strcmp(argv[i], shortened_specifier) == 0) {
		ensure(i + 1 < argc, INVALID_ARGUMENTS_MESSAGE);
		memcpy(argument_variable, argv[i + 1], sizeof(argv[i + 1]));
		i += 2;
		return true;
	}
	return false;
}

int main(int argc, const char** argv) {
	ensure(argc % 2 == 0, INVALID_ARGUMENTS_MESSAGE);
	
	char *ciphertext = (char*)malloc(256);

	char *dictionary_file = (char*)malloc(256);
	char *outfile = (char*)malloc(256);
	char *logfile = (char*)malloc(256);
	
	char *encryption_method = (char*)malloc(256);
	
	char *displayed_top = (char*)malloc(256);

	int i = 1;
	while (i < argc) {
		if (parse_argument(argc, argv, i, "--dictionary", "-D", dictionary_file)) {
			continue;
		}
		if (parse_argument(argc, argv, i, "--outfile", "-O", outfile)) {
			continue;
		}
		if (parse_argument(argc, argv, i, "--logfile", "-L", logfile)) {
			continue;
		}
		if (parse_argument(argc, argv, i, "--type", "-T", encryption_method)) {
			continue;
		}
		if (parse_argument(argc, argv, i, "--top", "-N", displayed_top)) {
			continue;
		}

		if (strlen(ciphertext)) {
			exit_with_message(INVALID_ARGUMENTS_MESSAGE);
		}
		memcpy(ciphertext, argv[i], sizeof(argv[i]));
		i++;
	}

	ensure(is_valid_dictionary_file(dictionary_file), INVALID_ARGUMENTS_MESSAGE);
	//ensure(is_valid_outfile(outfile), INVALID_ARGUMENTS_MESSAGE);
	//ensure(is_valid_logfile(logfile), INVALID_ARGUMENTS_MESSAGE);
	ensure(is_valid_encryption_method(encryption_method), INVALID_ARGUMENTS_MESSAGE);
	ensure(is_valid_displayed_top(displayed_top), INVALID_ARGUMENTS_MESSAGE);

	ensure(is_valid_ciphertext(ciphertext), INVALID_CIPHERTEXT_MESSAGE); 

	start(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top);

	return 0;
}
