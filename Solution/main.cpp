#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Benchmark/benchmark.h"

using namespace std;

struct comma_numpunct : std::numpunct<char> {
  char do_thousands_sep() const override { return ','; }
  std::string do_grouping() const override { return "\3"; }
};

// ==========================================
// 5. BASIC MAIN FUNCTION (FOR DEBUGGING)
// ==========================================
// NOTE: Students must write additional functions to load files, perform random
// sampling, measure execution time (chrono), and run the Benchmark loop to
// collect data for the report!
int main() {
  std::locale comma_locale(std::locale(), new comma_numpunct());
  std::cout.imbue(comma_locale);
  cout << "--- NLP PREPROCESSING SYSTEM ---" << endl;

  // 1. Read the dictionary
  vector<string> dictionary;
  ifstream dictFile("noise_dict_50k.txt");
  if (!dictFile.is_open()) {
    cerr << "Error: Cannot read noise_dict_50k.txt file\n";
    return 1;
  }
  string word;
  while (getline(dictFile, word)) {
    string cleanWord = "";
    for (char c : word) {
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
          (c >= '0' && c <= '9') || c == ' ') {
        cleanWord += c;
      }
    }
    if (!cleanWord.empty()) dictionary.push_back(cleanWord);
  }
  dictFile.close();
  cout << "Loaded " << dictionary.size() << " keywords into the dictionary.\n";

  runBenchmarkFixK(dictionary);
  runBenchmarkFixN(dictionary);

  return 0;
}
