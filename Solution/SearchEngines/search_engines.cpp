#include "search_engines.h"

#include <string>
#include <vector>

#include "../CoreStructure/Build/build.h"
#include "../CoreStructure/SortAlgorithm/sort_algorithm.h"
#include "../global_variables.h"

using namespace std;

// ==========================================
// 4. THE FOUR SEARCH ENGINES
// ==========================================

// TODO 6: Naive approach. Use 2 nested loops or std::string::find to find and
// mask with '*'
void naiveSearch(const vector<string> &dict, string &text) {
  int n = text.size();

  for (int k = 0; k < dict.size(); k++) {
    string keyword = dict[k];
    int m = keyword.size();

    for (int i = 0; i <= n - m; i++) {
      bool found = true;
      for (int j = i; j < i + m; j++) {
        if (text[j] != keyword[j - i]) {
          found = false;
          break;
        }
      }

      if (found == true) {
        for (int j = i; j < i + m; j++) {
          text[j] = '*';
        }
      }
    }
  }
}

// TODO 7: Traverse the text using the Trie. Need to implement backtracking
// logic when matching fails in the middle of a phrase.
void trieSearch(TrieNode *root, string &text) {
  for (int i = 0; i < text.size(); i++) {
    int j = i;
    TrieNode *current = root;
    while (j < text.size() && findChild(current, text[j])) {
      current = findChild(current, text[j]);
      if (current->is_end_of_word) {
        for (int k = i; k <= j; k++) {
          text[k] = '*';
        }
      }
      j++;
    }
  }
}

// TODO 8: Traverse the text using an optimized Trie with Maximal Munch
// (Greedy). When the longest phrase starting at position i is masked, the
// iterator i is allowed to jump.
void trieMaximalMunchSearch(TrieNode *root, string &text) {
  for (int i = 0; i < text.size();) {
    int longestEnd = -1;
    int j = i;
    TrieNode *current = root;
    while (j < text.size() && findChild(current, text[j])) {
      current = findChild(current, text[j]);
      if (current->is_end_of_word) {
        longestEnd = j;
      }
      j++;
    }

    if (longestEnd != -1) {
      for (int k = i; k <= longestEnd; k++) {
        text[k] = '*';
      }
      i = longestEnd + 1;
    } else {
      i++;
    }
  }
}

// TODO 9: Traverse the text using an Automaton (no backtracking).
// - Collect ALL overlapping results into a Match* array (statically allocated
// on the heap)
// - Call the sortMatches() function implemented above to sort.
// - Apply the Greedy algorithm to keep the longest non-overlapping intervals.
//   (Hint: Use a variable int last_end = -1. Iterate through the sorted Match
//   array, if match[i].start > last_end
//    then mask with '*' and update last_end = match[i].end. Otherwise skip it
//    because it is overlapped).
// - Execute the '*' masking and free the memory of the Match* array.
void ahoCorasickSearch(TrieNode *root, string &text) {
  Match *matches = new Match[OVERLAPPING_MAX];
  int matchSize = 0;

  TrieNode *current = root;
  for (int i = 0; i < text.size(); i++) {
    char c = text[i];

    while (current != root && findChild(current, c) == nullptr) {
      current = current->fail_link;
    }

    TrieNode *match = findChild(current, c);
    if (match == nullptr) {
      current = root;
    } else {
      current = match;
    }

    TrieNode *temp = current;
    while (temp != nullptr && temp != root) {
      if (temp->is_end_of_word) {
        matches[matchSize].start = i - temp->word_length + 1;
        matches[matchSize].end = i;
        matchSize++;
      }

      temp = temp->fail_link;
    }
  }

  if (matchSize > 0) {
    sortMatches(matches, matchSize);
  }

  int lastEnd = -1;
  for (int k = 0; k < matchSize; k++) {
    if (matches[k].start > lastEnd) {
      for (int i = matches[k].start; i <= matches[k].end; i++) {
        text[i] = '*';
      }
      lastEnd = matches[k].end;
    }
  }

  delete[] matches;
}
