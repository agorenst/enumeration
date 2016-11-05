//////////////////////////////////////////////////////////////////////////////
//
// This file contains algorithms for enumerating and exploring combinations,
// those (n choose k) sort of objects.
// The main algorithms here are from Knuth, the volume 4 fasciles.
//
// There are also variations, to make those algorithms in some way feel more
// "C++"-like. So we have iterators and things that mimic next_permutation
// and other modifications like that.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

//using namespace std;

typedef std::vector<int>::const_iterator enum_visitor_t;

// Algorithm L from fascile 3a.
// List out all combinations of size t with elements drawn from [0,n).
template<typename F>
void visit_all_combinations(int n, int t, F visitor) {
    assert(n > 0);
    assert(t > 0);
    assert(t < n);
    std::vector<int> c(t+2);
    // off by one error here...
    for (int k = 0; k < t; ++k) {
        c[k] = k;
    }
    c[t] = n;
    c[t+1] = 0;

    for(;;) {
        visitor(begin(c), begin(c)+t);
        int j = 0;
        while (c[j]+1 == c[j+1]) {
            c[j] = j;
            ++j;
        }
        if (j >= t) {
            return;
        }
        c[j]++;
    }
}


// Variation of algorithm L from fascile 3a.
// This is modified to feel more like "next_permutation", but
// because we have some placeholder values and state, it
// doesn't feel quite right. The input format is strange:
// It works for integers in [0,n], where array[t]=n, array[t+1]=0.
// (so for 8 choose 4, the input collection should be [0,1,2,3,8,0]).
template<class iter>
bool next_combination(iter start, iter end) {
    int j = 0;
    // we look for ``straight lines'', like 3456...
    // in doing so we reset it to 0123...
    while((*(start+j))+1 == *(start+(j+1))) {
        *(start+j) = j;
        ++j;
    }
    // if we get to the end in that process, that means we had 4,5,6,7,8,0, so we're done.
    if (start+j>=end-2) {
        return false;
    }
    // otherwise, we got to the next point, which we increment.
    *(start+j)=*(start+j)+1;
    return true;
}


// As next_combination is to algorithm L,
// this is to algorithm T. Supposedly the same thing, but faster.
template<class iter>
bool next_combination_static(iter start, iter end) {
    static const int l = std::distance(start,end-2);
    static const int n = *(end-2);
    static int j = l;
    // we're descending and incrementing:
    if (j > 0) {
        --j;
        *(start+j)=j+1;
        return true;
    }
    else {
        // so, j = -1
        // if we're in a case like 0345, then just do 1345, then 2345, etc.
        if ((*start)+1 < *(start+1)) {
            (*start)++;
            return true;
        }
        // otherwise, we want to set everything back to 012... until non-linear.
        // so, if we look like 2345...
        j = 0;
        while((*(start+j))+1 == *(start+j+1)) {
            *(start+j)=j; // reset 
            ++j;
        }
        // ok, now (start+j) is pointing to the unusual element: 0123[7], for instance.
        if (*(start+j) < n) { // we're not pointing to the last element
            //std::cout << "J: " << j << " " << n << std::endl;
            //std::cout << "Pre: " << *(start+j) << std::endl;
            *(start+j)=(*(start+j))+1;
            //std::cout << "Post: " << *(start+j) << std::endl;
            return true;
        }
        else {
            //std::cout << "J: " << j << " " << n << std::endl;
            return false;
        }
    }
}


