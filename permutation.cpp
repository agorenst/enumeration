#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>

using namespace std;
void printer(int* a) {
    for_each(a,a+4,[](int x) { cout << x << " "; }); cout << endl;
}

template<class IT>
void i_to_perm(IT most_significant, IT after_least_significant, int i) {
    //cout << "Original input: " << i << endl;

    // the 0-th permutation is no change at all. So too is the n!-th permutation.
    // The idea is that i must fit between some (n-1)! <= i < n!.
    // So i = (n-1)!*k + j, where j < (n-1)!
    // We observe that for the permutations starting at (n-1)! to n!-1, the
    // nth-least-significant digit is what's being swapped.
    // In particular, we swap it with the kth value.
    // we then sort the suffix
    while (i > 0) {
        //cout << "\ti         " << i << endl;
        int n = 1;
        int nfact = 1;

        // we want to apply the "largest" possible permutation
        // of one element. So, we find the largest factorial
        // that fits in our range. I.e., if i is between
        // (n-1)! and n!, then we're going to swap the (n-1)-st
        // element.
        while (nfact <= i) {
            ++n;
            nfact *= n;
        }
        //cout << "\tn         " << n << endl;
        //cout << "\tnfact     " << nfact << endl;
        // now we have i <= nfact
        auto k = i / (nfact/n); // integer division, truncates.
        //cout << "\tk         " << k << endl;
        assert(k <= (n-1)); // is that right? remember we're counting "backwards"...
        
        auto swapper1 = after_least_significant-n;
        //auto swapper2 = after_least_significant-k;
        auto swapper2 = swapper1+k;
        // check about stuff

        std::swap(*swapper1,*swapper2);
        //cout << "before sort" << endl;
        //printer(most_significant);
        std::sort(swapper1+1,after_least_significant);
        //cout << "after sort" << endl;
        //printer(most_significant);

        i -= (k*(nfact/n));
        //cout << "new i " << i << endl;
    }
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
}
