#include "enumeration.h"

using namespace std;
template<typename t>
ostream& operator<<(ostream& o, vector<t> a) {
    for (auto it = a.begin(); it != a.end(); ++it) {
        o << *it << " ";
    }
    return o;
}

//
// Lots of testing stuff here.
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


void test_correctness(unsigned n) {
    vector<int> a(n);
    for (unsigned i = 0; i < n; ++i) {
        a[i] = i;
    }
    auto b = a;
    do {
        if (a != b) {
            cout << "Error! " << a << "\t" << b << endl;
        }
        next_permutation(b.begin(), b.end());
    } while (next_perm(a.begin(), a.end()));
}

unsigned compute_mine(unsigned n) {
    vector<int> a(n);
    for (unsigned i = 0; i < n; ++i) {
        a[i] = i;
    }
    unsigned x = 0;
    do {
        ++x;
    } while(next_perm(a.begin(), a.end()));
    return x;
}

// times the built-in "next_permutation" method.
unsigned compute_system(unsigned n) {
    vector<int> a(n);
    for (unsigned i = 0; i < n; ++i) {
        a[i] = i;
    }
    unsigned x = 0;
    do {
        ++x;
    } while(next_permutation(a.begin(), a.end()));
    return x;
}

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

void test_comb(int n, int s) {
//    if (s > n/2) {
//        s = n-s;
//    }
    vector<int> a(s+2);
    for (int i = 0; i < s; ++i) {
        a[i] = i-0;
    }
    a[s+0]=n;
    a[s+1]=0;
    //cout << a << endl;
    unsigned x = 0;
    do {
        //cout << a << endl;
//        for (auto it = a.rbegin()+2; it != a.rend()+1; ++it) {
//            cout << *it << " ";
//        }
//        cout << endl;
        ++x;
    //} while(next_comb_first(a.begin(), a.end()));
    } while(next_comb(a.begin(), a.end()));
    cout << "Total: " << x << endl;
}

int main(int argc, char* argv[]) {
    test_comb(atoi(argv[1]), atoi(argv[2]));
//    match_to_parens();
    //test_match();
      //time_matching(atoi(argv[1]), atoi(argv[2]));
      //test_new_match_correctness(atoi(argv[1]));
//      time_old_match(atoi(argv[1]));
      //time_new_match(atoi(argv[1]));
//    test_perm_correctness_simple(5);
//    test_perm_correctness({1,2,3,3,3,4});
//    //cout << compute_mine(atoi(argv[1])) << endl;
//    const int len = 3;
//    //bool a[len] = {false, false, false, false, false};
//    bool a[len] = {false, false, false};
//    do {
//        for (int i = 0; i < len; ++i) {
//            cout << a[i] << " " ;
//        }
//        cout << endl;
//    } while(next_subset(a, a+len));
//    //cout << compute_system(atoi(argv[1])) << endl;
//    //
//    cout << endl;
//    vector<int> test = {1, 2, 3, 4, 5, 6, 7};
//    cout << retrieve(2,test) << endl;
//    cout << test << endl;
//    cout << retrieve(2,test) << endl;
//    cout << test << endl;
//    cout << retrieve(2,test) << endl;
//    cout << test << endl;
//    cout << retrieve(2,test) << endl;
//    cout << test << endl;
//    vector<int> make_me(4);
//    vector<int> valid_perm = {1,2,3,3};
//    vector<int> main_perm  = {1,2,3,3};
//    std::vector<int> perm4 = {1,2,3,3};
//    for (int i = 0; i < FACT[4]; ++i) {
//        int_to_perm(i, 4, make_me.begin(), perm4);
//        cout << make_me << "\t" << valid_perm << "\t" << main_perm << "\t" << (make_me == valid_perm) << "\t" << (valid_perm == main_perm) << endl;
//        next_perm(valid_perm.begin(), valid_perm.end());
//        next_permutation(main_perm.begin(), main_perm.end());
//    }
}
