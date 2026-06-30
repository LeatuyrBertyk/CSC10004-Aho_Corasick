#include "benchmark.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "../CoreStructure/Building/building.h"
#include "../CoreStructure/TrieMemoryManagement/trie_memory_management.h"
#include "../SearchEngines/search_engines.h"
#include "../global_variables.h"
#include "../trie_node.h"

using namespace std;

void runBenchmarkMode(int mode, const vector<string> &dict, TrieNode *root,
                      string &text) {
  auto startTime = chrono::high_resolution_clock::now();

  for (int i = 0; i < QUERY_COUNT; i++) {
    string textCopy = text;
    if (mode == 1) {
      naiveSearch(dict, textCopy);
    } else if (mode == 2) {
      trieSearch(root, textCopy);
    } else if (mode == 3) {
      trieMaximalMunchSearch(root, textCopy);
    } else if (mode == 4) {
      ahoCorasickSearch(root, textCopy);
    }
  }

  auto endTime = chrono::high_resolution_clock::now();
  auto duration =
      chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();

  switch (mode) {
  case 1:
    cout << "Naive Search:       ";
    break;
  case 2:
    cout << "Standard Trie:      ";
    break;
  case 3:
    cout << "Trie+Maximal Munch: ";
    break;
  case 4:
    cout << "Aho-Corasick:       ";
    break;
  }

  // cout << duration / QUERY_COUNT << " ns\n";
  cout << duration << " ns\n";
}

string generateText(const vector<string> &fullCorpus, long long N) {
  if (fullCorpus.empty()) {
    cerr << "FATAL ERROR: fullCorpus is empty\n";
    exit(1);
  }

  string result = "";
  result.reserve(N * 7);

  size_t size = fullCorpus.size();
  for (long long i = 0; i < N; i++) {
    result += fullCorpus[i % size] + " ";
  }
  return result;
}

void runBenchmarkFixK(const vector<string> &dict) {
  const int DATA_SIZES[] = {10000,   30000,   100000,  300000,
                            1000000, 3000000, 10000000};
  const int NUM_SIZES = sizeof(DATA_SIZES) / sizeof(DATA_SIZES[0]);

  vector<string> fullCorpus;
  ifstream corpusFile("clean_corpus.txt");
  string line;
  while (getline(corpusFile, line)) {
    stringstream ss(line);
    string word;
    while (ss >> word) {
      fullCorpus.push_back(word);
    }
  }
  corpusFile.close();

  cout << "\n========== BENCHMARK WITH FIX K = " << FIX_K << " ==========\n\n";

  vector<string> tempDict = dict;
  random_device rd;
  mt19937 g(rd());

  for (int i = 0; i < NUM_SIZES; i++) {
    int N = DATA_SIZES[i];
    string text = generateText(fullCorpus, N);

    shuffle(tempDict.begin(), tempDict.end(), g);
    vector<string> testDict;
    for (int j = 0; j < FIX_K && j < tempDict.size(); j++) {
      testDict.push_back(tempDict[j]);
    }
    TrieNode *root = createNode('/');
    for (const string &w : testDict)
      insertWord(root, w);
    buildFailureLinks(root);

    cout << "N = " << N << '\n';
    for (int mode = 1; mode <= 4; mode++) {
      runBenchmarkMode(mode, testDict, root, text);
    }
    cout << '\n';

    if (root) {
      freeTrie(root);
    }
  }
}

void runBenchmarkFixN(const vector<string> &dict) {
  vector<string> tempDict = dict;
  random_device rd;
  mt19937 g(rd());

  int DATA_SIZES[] = {1000, 3000, 5000, 10000, 30000, 50000};
  int NUM_SIZES = sizeof(DATA_SIZES) / sizeof(DATA_SIZES[0]);

  vector<string> fullCorpus;
  ifstream corpusFile("clean_corpus.txt");
  string line;
  while (getline(corpusFile, line)) {
    stringstream ss(line);
    string word;
    while (ss >> word) {
      fullCorpus.push_back(word);
    }
  }
  corpusFile.close();

  string text = generateText(fullCorpus, FIX_N);

  cout << "\n========== BENCHMARK WITH FIX N = " << FIX_N << " ==========\n\n";

  for (int i = 0; i < NUM_SIZES; i++) {
    int K = DATA_SIZES[i];

    shuffle(tempDict.begin(), tempDict.end(), g);
    vector<string> testDict;

    for (int j = 0; j < K && j < tempDict.size(); j++) {
      testDict.push_back(tempDict[j]);
    }

    TrieNode *root = createNode('/');
    for (const string &w : testDict)
      insertWord(root, w);
    buildFailureLinks(root);

    cout << "K = " << K << '\n';
    for (int mode = 1; mode <= 4; mode++) {
      runBenchmarkMode(mode, testDict, root, text);
    }
    cout << '\n';

    if (root) {
      freeTrie(root);
    }
  }
}
