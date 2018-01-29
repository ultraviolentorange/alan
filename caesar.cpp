#include "caesar.h"

#include "candidate_handler.h"
#include "cfg_handler.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void run_caesar() {
	std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top;
	load_cfg(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top);

	std::ofstream log(logfile);

	if (!logfile.empty()) {
		log << "Trying to decrypt Caesar...\n";
	} else {
		std::cout << "Trying to decrypt Caesar...\n";
	}

	for (int shift = 1; shift < 26; shift++) {
		std::string new_candidate;
		for (int i = 0; ciphertext[i]; i++) {
			char shifted = ciphertext[i];
			if ('a' <= ciphertext[i] && ciphertext[i] <= 'z') {
				shifted = (char)('a' + (ciphertext[i] - 'a' + shift) % 26);
			}
			if ('A' <= ciphertext[i] && ciphertext[i] <= 'Z') {
				shifted = (char)('A' + (ciphertext[i] - 'A' + shift) % 26);
			}
			new_candidate += shifted;
		}
		add_candidate(new_candidate);
	}
}