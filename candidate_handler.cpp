#include "candidate_handler.h"

#include "candidate_evaluator.h"
#include "cfg_handler.h"

#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<std::pair<int, std::string> > candidates;

int candidates_count() {
	return (int)candidates.size();
}

void add_candidate(std::string candidate) {
	candidates.push_back(std::make_pair(evaluate(candidate), candidate));
}

void display_candidates(int top) {
	sort(candidates.begin(), candidates.end());
	candidates.resize(unique(candidates.begin(), candidates.end()) - candidates.begin());
	reverse(candidates.begin(), candidates.end());
	
	std::cout << "\n";
	std::cout << "Total unique candidates generated: " << (int)candidates.size() << "\n";
	std::cout << "Displaying " << std::min(top, (int)candidates.size()) << " best in order of correctness probability...\n\n";
	for (int i = 0; i < std::min(top, (int)candidates.size()); i++) {
		std::cout << candidates[i].second << "\n";
	}
}

