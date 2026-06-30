#ifndef TRIE_MEMORY_MANAGEMENT_H
#define TRIE_MEMORY_MANAGEMENT_H

#include "../../trie_node.h"

TrieNode* createNode(char c);
void freeTrie(TrieNode* root);

#endif  // TRIE_MEMORY_MANAGEMENT_H