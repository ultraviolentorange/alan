#pragma once

#include <string>
#include <cstring>

void trie_add(int node, char c);
int trie_go(int node, char c);
void build_trie();
int evaluate(std::string candidate);