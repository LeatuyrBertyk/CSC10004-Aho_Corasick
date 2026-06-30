#ifndef SEARCH_ENGINES_H
#define SEARCH_ENGINES_H

#include <string>
#include <vector>

#include "../trie_node.h"

using namespace std;

void naiveSearch(const vector<string>& dict, string& text);
void trieSearch(TrieNode* root, string& text);
void trieMaximalMunchSearch(TrieNode* root, string& text);
void ahoCorasickSearch(TrieNode* root, string& text);

#endif  // SEARCH_ENGINES_H