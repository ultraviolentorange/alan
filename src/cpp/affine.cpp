#include "affine.h"

#include "candidate_handler.h"
#include "cfg_handler.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void run_affine() {
	std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top;
	load_cfg(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top);

	std::ofstream log(logfile);
	
	if (!logfile.empty()) 
		log << "Trying to decrypt Affine...\n";
	else 
		std::cout << "Trying to decrypt Affine...\n";

	for (int multiplier = 1; multiplier < 26; multiplier++) {
		for (int shift = 0; shift < 26; shift++) {
			std::string new_candidate;
			for (int i = 0; ciphertext[i]; i++) {
				char shifted = ciphertext[i];
				if ('a' <= ciphertext[i] && ciphertext[i] <= 'z') {
					shifted = (char)('a' + (multiplier * (ciphertext[i] - 'a') + shift) % 26);
				}
				if ('A' <= ciphertext[i] && ciphertext[i] <= 'Z') {
					shifted = (char)('A' + (multiplier * (ciphertext[i] - 'A') + shift) % 26);
				}
				new_candidate += shifted;
			}
			add_candidate(new_candidate);
		}
	}
}