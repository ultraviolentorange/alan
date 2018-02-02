#include "candidate_evaluator.h"

#include "cfg_handler.h"

#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <set>

std::map<char, int> trie[9000000]; 
std::set<int> terminating;

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
	std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key;
	load_cfg(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key);

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
		terminating.insert(current_node);
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
			if (terminating.find(current_node) != terminating.end()) {
				res += 10 * std::max(0, j - i - 2);
			}
			if (current_node == 0 || j == len - 1) {
				res += (j - i);
				break;
			}
		}
	}

	return res;
}