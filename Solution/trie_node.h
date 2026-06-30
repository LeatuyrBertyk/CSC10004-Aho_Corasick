#ifndef TRIE_NODE_H
#define TRIE_NODE_H

// 1. Auxiliary structure to solve the Maximal Munch problem (Preventing overlapping matches)
// start is the starting index, end is the index of the last character (Inclusive).
// Example: If the pattern 'abc' appears at the beginning of the string (index 0), then start=0, end=2.
struct Match {
    int start;
    int end;
};

// 2. Core Node structure for the Aho-Corasick algorithm
struct TrieNode {
    char character;             // The character at this node
    bool is_end_of_word;        // Marks if this node is the end of a noise phrase
    int word_length;            // The length of the phrase (used to mask with '*' characters)
    
    // Failure link for the Automaton algorithm
    TrieNode* fail_link;        
    
    // --- CHILD NODE MANAGEMENT USING LINKED LIST ---
    TrieNode* first_child;      // Pointer to the FIRST child node of the current node
    TrieNode* next_sibling;     // Pointer to the NEXT SIBLING node (same parent)
};

#endif // TRIE_NODE_H
