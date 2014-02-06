#include "enumeration.h"

using namespace std;

// debugging: let's print a vector of elements
template<typename t>
ostream& operator<<(ostream& o, vector<t> a) {
    for (auto it = a.begin(); it != a.end(); ++it) {
        o << *it << " ";
    }
    return o;
}

//
// These first two functions test the correctness of my
// permutation implementation, from Knuth
//
void test_perm_correctness_simple(unsigned int n) {
    vector<int> a(n);
    for (unsigned i = 0; i < n; ++i) {
        a[i] = i;
    }
    auto b = a;
    bool built_in, my_imp;
    do {
        if (a != b) {
            cout << "Error! " << a << "\t" << b << endl;
        }
        built_in = next_permutation(b.begin(), b.end());
        my_imp = next_perm(a.begin(), a.end());
    } while(built_in && my_imp);
    cout << "Do they both end at the same time?" << "\t" << (built_in == my_imp) << endl;
    cout << "Are they in the equal state at the end? " << (a == b) << endl;
}

void test_perm_correctness(vector<int> tester) {
    auto a = tester;
    auto b = tester;
    bool built_in, my_imp;
    do {
        if (a != b) {
            cout << "Error! " << a << "\t" << b << endl;
        }
        built_in = next_permutation(b.begin(), b.end());
        my_imp = next_perm(a.begin(), a.end());
    } while(built_in && my_imp);
    cout << "Do they both end at the same time? "<< (built_in == my_imp) << endl;
    cout << "Are they in the equal state at the end? " << (a == b) << endl;
}

//
// this is a timing experiment for the permutations.
//
unsigned time_permutation(unsigned n, bool mine = true) {
    vector<int> a(n);
    for (unsigned i = 0; i < n; ++i) {
        a[i] = i;
    }
    unsigned x = 0;
    if (mine) {
        do {
            ++x;
        } while(next_perm(a.begin(), a.end()));
    }
    else {
        do {
            ++x;
        } while(next_permutation(a.begin(), a.end()));
    }
    return x;
}

//==========================
// Testing the matching permutation
//==========================

void test_match() {
    vector<int> a = {1,2,3,4,5,6};
    do {
    cout << a << endl;
    } while(next_match(a.begin(), a.end()));
}

void test_new_match_correctness(int n) {
    vector<int> a(n);
    for (auto i = 0; i < n; ++i) {
        a[i] = i;
    }
    auto b = a;
    do {
        if (a != b) {
            cout << "Error!" << endl;
        }
        next_match(a.begin(), a.end());
    } while(next_match_first(b.begin(), b.end()));
}

void time_matching(int n, int version) {
    vector<int> a(n);
    for (auto i = 0; i < n; ++i) {
        a[i] = i;
    }
    unsigned long c = 0;
    bool notdone = true;
    while (notdone) {
        ++c;
        switch(version) {
            case 1:
                notdone = next_match_first(a.begin(), a.end());
                break;
            case 2:
                notdone = next_match_second(a.begin(), a.end());
                break;
            case 3:
                notdone = next_match(a.begin(), a.end());
                break;
        }
    }
    cout << c << endl;
}

// used to show that the distinct matchings (labeled) are distinct
// from the matching parens---that is, the natural encoding from
// labeled matchings to matching parens is many-to-one
void match_to_parens() {
    vector<int> a = {0,1,2,3,4,5,6,7};
    vector<char> b(a.size());
    cout << b.size() << endl;
    do {
        for (auto it = a.begin(); it != a.end(); it += 2) {
            b[*it] = '(';
            b[*(it+1)] = ')';
        }
        cout << b << endl;
    } while(next_match(a.begin(), a.end()));
}

//=========================
// Testing the combination code
//=========================

void test_comb(int n, int s) {
    vector<int> a(s+2);
    for (int i = 0; i < s; ++i) {
        a[i] = i-0;
    }
    a[s+0]=n;
    a[s+1]=0;
    //cout << a << endl;
    unsigned x = 0;
    do {
        ++x;
    } while(next_comb(a.begin(), a.end()));
    cout << "Total: " << x << endl;
}

void print_comb(int n, int k) {
    vector<int> a(k+2);
    for (int i = 0; i < k; ++ i) {
        a[i] = i -0;
    }
    a[k+0] = n;
    a[k+1] = 0;
    do {
        for (auto it = a.begin(); it != a.end()-2; ++it) {
            cout << *it << " ";
        }
        cout << endl;
    } while(next_comb(a.begin(), a.end()));
}

int main(int argc, char* argv[]) {
    print_comb(atoi(argv[1]), atoi(argv[2]));
}
