#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>

// Developed without any explicit reference, though I've done similar things
// before. I think Knuth has a nice collection of these. We trust that the input
// is already sorted and each element unique. The algorithm can be improved
// (we don't need sort, and in practice the while-loop can be a lookup table)
// and more robust, but it's a perfectly fine starting point, and a neat
// example of exploring self-reducible algorithms.
template<class IT>
void i_to_perm(IT most_significant, IT after_least_significant, int i) {
    while (i > 0) {
        int n = 1;
        int nfact = 1;

        while (nfact <= i) {
            ++n;
            nfact *= n;
        }
        auto k = i / (nfact/n);

        auto swapper1 = after_least_significant-n;
        auto swapper2 = swapper1+k;

        std::swap(*swapper1,*swapper2);
        // overkill
        std::sort(swapper1+1,after_least_significant);

        i -= (k*(nfact/n));
    }
}
bool test_execution() {
    int a[] = {0,1,2,3};
    int b[] = {0,1,2,3};
    i_to_perm(a,a+4,4);
    // we expect a = {1 4 2 3}
    for(int i = 0; i < 4; ++i) {
        next_permutation(b,b+4);
    }
    for (int i = 0; i < 4; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

using namespace std;
void printer(int* a) {
    for_each(a,a+4,[](int x) { cout << x << " "; }); cout << endl;
}

int main() {
    int a[] = {1,2,3,4};
    do {
        printer(a);
    } while(next_permutation(a, a+4));
    sort(a,a+4);
    //printer(a);
    cout << endl;
    for (int i = 0; i < 24; ++i) {
        sort(a,a+4);
        //printer(a);
        i_to_perm(a,a+4,i);
        printer(a);
        //printer(a);
    }
    cout << test_execution() << endl;
}
