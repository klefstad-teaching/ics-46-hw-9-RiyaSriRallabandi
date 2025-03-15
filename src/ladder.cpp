#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << msg << " " << word1 << ", " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) {return false;}

    vector<int> previous_row(len2 + 1);
    vector<int> current_row(len2 + 1);

    for (int j = 0; j <= len2; j++) {previous_row[j] = j;}

    for (int i = 1; i <= len1; i++) {
        current_row[0] = i;
        
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                current_row[j] = previous_row[j - 1];
            } else {
                current_row[j] = 1 + min({previous_row[j], current_row[j - 1], previous_row[j - 1]});
            }
        } previous_row = current_row;
    } return previous_row[len2] <= d;
}