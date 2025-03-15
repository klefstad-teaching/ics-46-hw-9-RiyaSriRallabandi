#include <iostream>
#include <string>
#include "ladder.h"

int main () {
    string start_word, end_word;
    cout << "Enter the start word: ";
    cin >> start_word;
    cout << "Enter the end word: ";
    cin >> end_word;

    if (start_word == end_word) {
        error(start_word, end_word, "ERROR: Start and end words are the same.");
        return 1;
    }
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
    return 0;
}