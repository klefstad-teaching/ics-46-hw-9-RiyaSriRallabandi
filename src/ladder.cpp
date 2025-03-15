#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << msg << " " << word1 << ", " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int str1_length = str1.length();
    int str2_length = str2.length();

    if (abs(str1_length - str2_length) > d) {return false;}

    vector<int> previous_row(str2_length + 1);
    vector<int> current_row(str2_length + 1);

    for (int j = 0; j <= str2_length; j++) {previous_row[j] = j;}

    for (int i = 1; i <= str1_length; i++) {
        current_row[0] = i;
        
        for (int j = 1; j <= str2_length; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                current_row[j] = previous_row[j - 1];
            } else {
                current_row[j] = 1 + min({previous_row[j], current_row[j - 1], previous_row[j - 1]});
            }
        } previous_row = current_row;
    } return previous_row[str2_length] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    int word1_length = word1.length();
    int word2_length = word2.length();

    if (abs(word1_length - word2_length) > 1) {return false;}

    int changes = 0;
    int i = 0, j = 0;

    while (i < word1_length && j < word2_length) {
        if (word1[i] == word2[j]) {
            i++; j++;
        } else {
            changes++;
            if (changes > 1) {return false;}
            if (word1_length > word2_length) {i++;}
            else if (word1_length < word2_length) {j++;}
            else {i++; j++;}
        }
    } if (i < word1_length || j < word2_length) {changes++;}
    return changes == 1;
 }

 vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) {return {};}
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = current_ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);

                if (word == end_word) {return new_ladder;}
                ladder_queue.push(new_ladder);
            }
        }
    } return {};
 }

 void load_words(set<string> & word_list, const string& file_name) {
    ifstream input_file(file_name);
    if (!input_file.is_open()) {
        error("", "", "Error: Unable to open file " + file_name);
        return;
    }
    string word;
    while (input_file >> word) {
        for (char& c : word) {
            c = tolower(c);
        } word_list.insert(word);
    } input_file.close();
 }

 void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;}
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    } cout << endl;
 }

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}