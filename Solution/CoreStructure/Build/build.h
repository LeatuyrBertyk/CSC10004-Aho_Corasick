#ifndef BUILD_H
#define BUILD_H

#include <string>

#include "../../trie_node.h"

using namespace std;

void insertWord(TrieNode *root, const string &word);
TrieNode *findChild(TrieNode *node, char c);
void buildFailureLinks(TrieNode *root);

#endif // BUILD_H
