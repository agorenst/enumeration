// This is the main file.
// You can specify arguments to list out
// certain combinatoric arguments.

// Each header includes the algorithms
// concerning the named combinatoric object.
#include "combination.h"
#include "matching.h"
#include "permutation.h"
#include "subset.h"

#include <array>
#include <algorithm>

// Testing combination.h functions:

using namespace std;

void test_all_combination_functions() {
    // list out all combinations
    visit_all_combinations(5, 2, [](enum_visitor_t begin, enum_visitor_t end){
                                        for (; begin != end; ++begin) {
                                            cout << *begin << " ";
                                        }
                                        cout << endl;
                                    });
    cout << endl;

    //int next_tester[] = {0,1,2,3,8,0};
    int next_tester[] = {0,1,5,0};
    do {
        for (auto it = begin(next_tester); it != end(next_tester)-2; ++it) {
            cout << *it << " ";
        }
        cout << endl;
    } while (next_combination(begin(next_tester), end(next_tester)));

    cout << endl;

    next_tester[0] = 0;
    next_tester[1] = 1;
    next_tester[2] = 5;
    next_tester[3] = 0;
    do {
        for (auto it = begin(next_tester); it != end(next_tester)-2; ++it) {
            cout << *it << " ";
        }
        cout << endl;
    } while (next_combination_static(begin(next_tester), end(next_tester)));

}

int* make_array(int n) {
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
    return a;
}

bool test_all_permutation_functions() {
    const int n = 4;
    int* a = make_array(n);
    int i = 0;
    do {
        auto b = i_to_perm(n,i);
        for (int j = 0; j < n; ++j) {
            assert(b[j] == a[j]);
        }
        // verbose, to check that it really does produce the output we expect.
        //for_each(a, a+n, [](int x) { cout << x << " "; }); cout << endl;
        //for_each(begin(b), begin(b)+n, [](int x) { cout << x << " "; }); cout << endl;
        ++i;

    // Note that "next_perm" is ours, and "next_permutation" is the standard's.
    //} while(next_permutation(a, a+n));
    } while(next_perm(a,a+n));
    delete [] a;
    return true;
}

// Pretty sparse algorithms so far...
void test_all_subset_functions() {
    array<bool,6> subset_tester;
    for (auto& b : subset_tester) {
        b = false;
    }
    do {
        for_each(begin(subset_tester), end(subset_tester), [](bool b) {
            cout << b << " ";
        }); cout << endl;
    } while(next_subset(begin(subset_tester), end(subset_tester)));

}

int main() {
}
