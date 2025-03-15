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
            if (str1_length[i - 1] == str2_length[j - 1]) {
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