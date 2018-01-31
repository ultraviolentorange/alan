#include "atbash.h"

#include "candidate_handler.h"
#include "cfg_handler.h"

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

void run_atbash() {
	std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key;
	load_cfg(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key);

	std::ofstream log(logfile);

	if (!logfile.empty()) {
		log << "Trying to decrypt Atbash...\n";
	} else {
		std::cout << "Trying to decrypt Atbash...\n"; 
	}

	std::string candidate = ciphertext;
	for (int i = 0; i < (int)candidate.size(); i++) {
		if ('a' <= candidate[i] && candidate[i] <= 'z') {
			candidate[i] = (char)('z' - candidate[i] + 'a');
		} 
		if ('A' <= candidate[i] && candidate[i] <= 'Z') {
			candidate[i] = (char)('Z' - candidate[i] + 'A');
		}
	}

	add_candidate(candidate);
}