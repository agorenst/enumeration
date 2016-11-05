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

void printer(int* a, int n = 4) {
    for_each(a,a+n,[](int x) { cout << x << " "; }); cout << endl;
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

int* make_array(int n) {
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
    return a;
}

bool test(int n) {
    int* a = make_array(n);
    int i = 0;
    do {
        auto b = i_to_perm(n,i);
        for (int j = 0; j < n; ++j) {
            if (b[j] != a[j]) { return false; }
            //assert(b[j] == a[j]);
        }
        // verbose, to check that it really does produce the output we expect.
        //printer(a,n);
        //printer(b);
        ++i;
    } while(next_permutation(a, a+n));
    delete [] a;
    return true;
}

// let's be real about the best way to compute factorial.
// todo: fill in the remaining values...
const long long int FACT[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

// algorithm informed by knuth, vol4.
// finds the next permutation in [start,end)
// Curiously, seems to be faster than the built-
// in version of this function. Why?
template<typename iter>
bool next_perm(const iter start, const iter end) {
    if (start == end || start + 1 == end) {
        return false; // trivial permutation.
    }
    auto j = end;
    --j; // point to the last *valid* element


    // we set j to point to the first element that's ``in order''
    // of course j must first point to the n-2nd element
    // it *is* valid that j could be start.
    do {
        --j;
        if (j < start) {
            // we sort so that after the  do {...}while(next_perm)
            // runs, the state is in sorted order after the loop.
            std::sort(start, end);
            return false;
        }
    } while(*j >= *(j+1));

    // note that if we get to this point, *j < *(j+1), but also j >= start.
    auto l = end;

    // find the first element we can swap with j;
    // we assume that \exists an element in [j, end) larger than j
    // Observe that *(j+1) > *j, so we will succeed.
    do {
        --l;
    } while (*j >= *l);

    std::swap(*j,*l);

    // with the swap done, we sort the remaining elements.
    std::reverse(j+1,end);
    return true;
}




int main() {
    assert(test(0));
    assert(test(1));
    assert(test(2));
    assert(test(3));
    assert(test(4));
    assert(test(5));
    assert(test(6));
    assert(test(7));
}
