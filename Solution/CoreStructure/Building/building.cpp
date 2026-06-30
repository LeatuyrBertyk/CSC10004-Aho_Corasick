#include "building.h"

#include <queue>
#include <string>

#include "../../trie_node.h"
#include "../TrieMemoryManagement/trie_memory_management.h"

using namespace std;

// ==========================================
// 3. BUILDING TRIE AND FAILURE LINKS
// ==========================================

// TODO 4: Insert a word into the Trie using linked lists (first_child,
// next_sibling)
void insertWord(TrieNode* root, const string& word) {
  TrieNode* current = root;

  for (char c : word) {
    if (current->first_child == nullptr) {
      current->first_child = createNode(c);
      current = current->first_child;
    } else {
      TrieNode* child = current->first_child;
      TrieNode* prev = current->first_child;

      while (child && child->character != c) {
        prev = child;
        child = child->next_sibling;
      }

      if (child == nullptr) {
        child = createNode(c);
        prev->next_sibling = child;
      }

      current = child;
    }
  }

  current->is_end_of_word = true;
  current->word_length = word.size();
}

// TODO 5: Use Queue (std::queue) to traverse BFS and compute fail_link pointers
// Hint: Because the Trie uses Linked Lists (first_child, next_sibling) instead
// of a children[256] array, you should write an auxiliary function `TrieNode*
// findChild(TrieNode* node, char c)` to easily find the child node when
// building fail_links.
TrieNode* findChild(TrieNode* node, char c) {
  if (node == nullptr || node->first_child == nullptr) {
    return nullptr;
  }

  for (TrieNode* child = node->first_child; child;
       child = child->next_sibling) {
    if (child->character == c) {
      return child;
    }
  }
  return nullptr;
}
void buildFailureLinks(TrieNode* root) {
  if (root == nullptr) {
    return;
  }

  root->fail_link = nullptr;

  queue<TrieNode*> que;

  TrieNode* child = root->first_child;
  while (child) {
    child->fail_link = root;
    que.push(child);
    child = child->next_sibling;
  }

  while (!que.empty()) {
    TrieNode* current = que.front();
    que.pop();

    TrieNode* v = current->first_child;
    while (v) {
      char c = v->character;

      TrieNode* fallback = current->fail_link;
      while (fallback != root && findChild(fallback, c) == nullptr) {
        fallback = fallback->fail_link;
      }

      TrieNode* match = findChild(fallback, c);
      if (match == nullptr) {
        v->fail_link = root;
      } else {
        v->fail_link = match;
      }

      que.push(v);
      v = v->next_sibling;
    }
  }
}