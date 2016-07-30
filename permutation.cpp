#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
int fact[] = {
    1,
    1,
    2,
    6,
    24,
    120,
    720 // etc...
};

void printer(int* a) {
    for_each(a,a+4,[](int x) { cout << x << " "; }); cout << endl;
}
void printer(std::vector<int>& a) {
    for_each(a.begin(),a.end(),[](int x) { cout << x << " "; }); cout << endl;
}

// Developed without any explicit reference, though I've done similar things
// before. I think Knuth has a nice collection of these. We trust that the input
// is already sorted and each element unique. The algorithm can be improved
// (we don't need sort, and in practice the while-loop can be a lookup table)
// and more robust, but it's a perfectly fine starting point, and a neat
// example of exploring self-reducible algorithms.
std::vector<int> i_to_perm(const int N, int i) {
    std::vector<int> p(N);

    for (int k = 0; k < N; ++k) { p[k] = k; }

    for (int n = N-1; n > 0; --n) {

        int j = i / fact[n]; // which is the j-th chunk of size fact[n] our input fits in?
        int w = (N-1)-n; // we need to swap the element we're "writing", and reverse our index.
        int s = w+j; // the s-th largest element in [w,end)

        //if (j == 0) { continue; } // mathematically this isn't needed. Optimization!
        std::swap(p[w],p[s]);

        // we can do better, knowing that there's exactly 1 out-
        // of-place element. But for now...
        std::sort(p.begin()+w+1,p.end());
        i -= j*fact[n];
    }
    return p;
}

int main() {
    int a[] = {0,1,2,3};
    int i = 0;
    do {
        printer(a);
        auto b = i_to_perm(4,i);
        printer(b);
        for (int j = 0; j < 4; ++j) {
            assert(b[j] == a[j]);
        }
        ++i;
    } while(next_permutation(a, a+4));
}
