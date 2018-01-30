#include "alan_brain.h"

#include "caesar.h"
#include "affine.h"

#include "candidate_handler.h"
#include "cfg_handler.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>

void start() {	
	std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key;
	load_cfg(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key);

	std::cout << "\033[2J\033[1;1H";
	std::ifstream ascii_art_file("ascii_art.txt");
	std::string art_line;
	for (; getline(ascii_art_file, art_line); ) {
		std::cout << art_line << "\n";
	} 

	std::cout << "\nStarting alan v1.0...\n\n[Configuration]\n";
	
	std::cout << "Dictionary file:   ";
	if (!dictionary_file.empty()) { 
		std::cout << dictionary_file << "\n"; 
	} else {
		dictionary_file = "dict.txt"; 
		std::cout << "default (dict.txt)\n";
	}

	std::cout << "Outfile:           ";
	if (!outfile.empty()) {
		std::cout << outfile << "\n";
	} else {
		std::cout << "default (stdout)\n";
	}

	std::cout << "Logfile:           ";
	if (!logfile.empty()) {
		std::cout << logfile << "\n";
	} else {
		std::cout << "default (stdout)\n";
	}

	std::cout << "Encryption method: ";
	if (!encryption_method.empty()) {
		std::cout << encryption_method << "\n";
	} else {
		std::cout << "unknown\n";
	}

	std::cout << "Displayed top:     ";
	if (!displayed_top.empty()) {
		std::cout << displayed_top << "\n";
	} else {
		std::cout << "default (100)\n";
	}

	std::cout << "\n";

	usleep(500000);

	std::ofstream log(logfile);

	if (encryption_method.empty() || encryption_method == "caesar") {
		const int candidates_before = candidates_count();
		run_caesar();
		const int candidates_after = candidates_count();
		if (!logfile.empty()) {
			log << "Successfully generated and added " << candidates_after - candidates_before << " candidates.\n";
		} else {
			std::cout << candidates_after - candidates_before << " candidates added.\n";
		}
	}
	std::cout << "\n";
	usleep(100000);

	if (encryption_method.empty() || encryption_method == "affine") {
		const int candidates_before = candidates_count();
		run_affine();
		const int candidates_after = candidates_count();
		if (!logfile.empty()) {
			log << "Successfully generated and added " << candidates_after - candidates_before << " candidates.\n";
		} else {
			std::cout << candidates_after - candidates_before << " candidates added.\n";
		}
	}
	std::cout << "\n";
	usleep(100000);

	int top = 100;
	if (!displayed_top.empty()) {
		top = 0;
		for (int i = 0; i < (int)displayed_top.size(); i++) {
			top = 10 * top + displayed_top[i] - '0';
		}
	}

	display_candidates(top);

}
