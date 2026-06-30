#include "trie_memory_management.h"

#include "../../trie_node.h"

// ==========================================
// 2. TRIE MEMORY MANAGEMENT
// ==========================================

// TODO 2: Dynamically allocate a new Node and manually initialize its fields
// (Assign nullptr to pointers, false to is_end_of_word, etc...)
TrieNode *createNode(char c) {
  return new TrieNode{c, false, 0, nullptr, nullptr, nullptr};
}

// TODO 3: Traverse the tree and free memory (delete) to prevent Memory Leak
void freeTrie(TrieNode *root) {
  if (root == nullptr) {
    return;
  }

  freeTrie(root->first_child);
  freeTrie(root->next_sibling);

  delete root;
  root = nullptr;
}
