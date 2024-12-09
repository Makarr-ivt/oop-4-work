#include "HashTableV1.hpp"
#include "HashTableV2.hpp"
#include "tests.hpp"
#include <iostream>
#include <string>
using namespace std;


void translate_sequence();
static const HashTableV2<string, string> aminoacids("D:/oop_4_work_final/entry_point/aminoacids.txt");
int main() {
    if (run_all_tests<HashTableV2<string, string>>() != 0) {
        return 1;
    }
    aminoacids.print();
    translate_sequence();
    return 0;
}

void translate_sequence() {
    string input;
    cout << "Enter nucleotide sequence (e.g., UUUUUCUUA):\n";
    cin >> input;

    vector<string> input_codons;
    string codon;
    auto char_count = 0;
    for (char c : input) {
        codon += c;
        ++char_count;
        if (char_count == 3) {
            char_count = 0;
            input_codons.push_back(codon);
            codon.clear();
        }
    }
    cout << "Amino acids sequence:\n";
    for (const auto& codon : input_codons) {
        if (aminoacids.is_contains(codon)) {
            cout << aminoacids[codon] << endl;
        } else {
            cout << "[Unknown codon: " << codon << "]\n";
        }
    }
}