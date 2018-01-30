#include "candidate_evaluator.h"

#include "cfg_handler.h"

#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>

std::map<char, int> trie[50000]; 

int trie_nodes = 1;

void trie_add(int node, char c) {
	trie[node][c] = trie_nodes++;
}

int trie_go(int node, char c) {
	if (!trie[node].count(c)) return 0;
	return trie[node][c];
}

bool tree_built = false;
void build_trie() {
	std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top;
	load_cfg(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top);

	std::ifstream dictionary(dictionary_file);
	std::string word;
	for (; getline(dictionary, word); ) {
		int current_node = 0;
		for (int i = 0; i < (int)word.size(); i++) {
			if (!trie_go(current_node, word[i])) {
				trie_add(current_node, word[i]);
			} 
			current_node = trie_go(current_node, word[i]);
		}
	}
	tree_built = true;
	std::ofstream log(logfile);
	if (!logfile.empty()) {
		log << "Successfully built dictionary prefix tree with " << trie_nodes << " node(s).\n"; 
	} else {
		std::cout << "Successfully built dictionary prefix tree with " << trie_nodes << " node(s).\n";
	}
}

std::string filter_candidate(std::string candidate) {
	std::string filtered;
	for (int i = 0; i < (int)candidate.size(); i++) {
		if ('a' <= candidate[i] && candidate[i] <= 'z') {
			filtered += candidate[i];
		} else if ('A' <= candidate[i] && candidate[i] <= 'Z') {
			filtered += (char)('a' + candidate[i] - 'A');
		}
	}
	return filtered;
}

int evaluate(std::string candidate) { 
	if (!tree_built) build_trie();
	candidate = filter_candidate(candidate);
	
	int len = (int)candidate.size();
	int res = 0;

	for (int i = 0; i < len; i++) {
		int current_node = 0;
		for (int j = i; j < len; j++) {
			current_node = trie_go(current_node, candidate[j]);
			if (current_node == 0 || j == len - 1) {
				res += (j - i) * len;
				break;
			}
		}
	}

	return res;
}