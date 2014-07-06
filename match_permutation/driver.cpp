#include "first_match.h"
#include "second_match.h"
#include "third_match.h"
#include "brute_force_match_perm.h"

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

vector<int> generate_start(int n) {
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        s[i] = i+1;
    }
    return s;
}

template<bool (*f)(vector<int>::iterator, vector<int>::iterator)>
long long time_enum(vector<int> s) {
    long long count = 0;
    do {
        ++count;
    } while(f(s.begin(), s.end()));
    cout << count << endl;
    return count;
}

// the basic timing format etc. was taken from a stackoverflow post.
//http://stackoverflow.com/questions/459691/best-timing-method-in-c
template<long long (*f)(vector<int>)>
void time_f(vector<int> s) {
    clock_t time_start, time_end;
    time_start = clock();
    long long x = f(s);
    time_end = clock() - time_start;
    int msecs = time_end * 1000 / CLOCKS_PER_SEC;
    cout << "Seconds: " << msecs / 1000 << ", Milliseconds: " << msecs % 1000 << endl;
}

// This compares timing between stuff.
int main(int argc, char* argv[]) {
    auto s = generate_start(atoi(argv[1]));
    time_f<time_enum<next_match>>(s);
    time_f<time_enum<next_match_second>>(s);
    time_f<time_enum<next_match_first>>(s);
}


/*

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

*/
