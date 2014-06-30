#include "first_match.h"
#include "second_match.h"
#include "third_match.h"
#include "brute_force_match_perm.h"

#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& o, vector<int> a) {
    for (int x : a) {
        o << x << " ";
    }
    return o;
}

bool test_algorithm() {
//    vector<int> a = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
//    vector<int> b = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    //vector<int> o = {1,2,3,4,5,6,7,8,9,10};
    vector<int> o = {1,2,3,4,5,6,7,8,9,10,11,12};
    vector<int> a = o;
    vector<int> b = o;
    do {
        cout << a << "\t" << b << endl;
        if (!std::equal(a.begin(), a.end(), b.begin())) {
            return false;
        } 
        simple_match(a.begin(), a.end());
    } while (next_match(b.begin(), b.end()));
    if (!(a == b && b == o)) {
        cout << a << endl
             << b << endl
             << o << endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    cout << test_algorithm() << endl;
    //vector<int> a = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
//    vector<int> a = {1,2,3,4,5,6};
//    do {
//        cout << a << endl;
//    } while(simple_match(a.begin(), a.end()));
    //} while(next_match(a.begin(), a.end()));
}
