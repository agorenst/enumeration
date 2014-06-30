#include <iostream>
#include <vector>
#include <string>
#include "third_match.h"

using namespace std;

const string usage_string = "Usage: ./match_perm_printer k, where k is an even int between 2 and 22";
const string error_string = "Error: k must be even, between 2 and 22, and even.";


ostream& operator<<(ostream& o, vector<int> a) {
    for (int x : a) {
        o << x << " ";
    }
    return o;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << usage_string << endl;
        return -1;
    }
    int k = atoi(argv[1]);
    if (!(k >= 2 && k < 24 && k % 2 == 0)) {
        cout << error_string << endl;
    }
    vector<int> matches(k);
    for (int i = 1; i <= k; ++i) {
        matches[i-1] = i;
    }

    do {
        cout << matches << endl;
    } while(next_match(matches.begin(), matches.end()));
}
