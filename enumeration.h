#ifndef _ENUMERATION_H_
#define _ENUMERATION_H_

#include <vector>
#include <algorithm>
#include <iostream>

const long long int FACT[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

template<typename iter>
void print_range(iter a, iter b) {
    std::cout << "printing range " << *a << " " << *b << std::endl;
    while (a != b) {
        std::cout << *a << std::endl;
        ++a;
    }
    std::cout << "done printing range" << std::endl;
}


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


// The third (and final?) version of my "match" enumerator.
// This exploits the sorting invariant I explored in the second
// edition, but now fully. Very fast!
// In particualr, we no longer actually call sort.
// Instead, we can maintain a sorted order with only a few simple loops
// each iteration.
template<typename iter>
bool next_match(const iter start, const iter end) {
    // invariant: [stack,end) is sorted.
    for (auto stack = end-2; stack != start; stack -= 2) {

        // the current y is stack-1, and the current x is stack-2
        auto old_y = stack-1;

        // we "unmatch" (stack-2,stack-1). So we place
        // stack-1 (old_y) back into the sorted list.
        // This maintains the invariant that [stack,end) is sorted.
        while((old_y+1) != end && *(old_y) > *(old_y+1)) {
            std::swap(*old_y,*(old_y+1));
            ++old_y;
        }
        // we place (stack-1) at old_y.
        // The location \emph{after} old_y, then, is exactly the
        // smallest value still-larger than our previous match.
        auto new_y = old_y+1;

        // if new_y != end, then that means there's a new candidate
        // that can be matched with old_x = stack-2.
        if (new_y != end) {
            // we set stack-1 (the y that old_x is matched with) to this value.
            std::swap(*new_y,*(stack-1));

            // but then we need to restore the sorted-ness invariant.
            while((new_y-1) >= stack && *(new_y) < *(new_y-1)) {
                std::swap(*new_y,*(new_y-1));
                --new_y;
            }
            return true;
        }

        // if new_y == end, then that means old_x can't be matched with
        // anything else (yet), so we have to repeat the process.
    } 
    return false;
}

// this is the second attempt at next_match.
// The key insight here is a tighter enumeration from the fact that
// the elements after the last-changed pair are in sorted order
template<typename iter>
bool next_match_second(const iter start, const iter end) {
    for (auto stack = end-2; stack != start; stack -= 2) {
        // the current y is stack-1, and the current x is stack-2
        std::sort(stack,end);
        auto old_y = stack-1;
        auto new_y = std::upper_bound(stack, end, *old_y);
//        std::cout << "Stack: " << *stack << std::endl;
//        std::cout << "Old y: " << *old_y << std::endl;
//        std::cout << "New y: " << *new_y << std::endl;
        if (new_y != end) {
            //std::cout << "Ending" << std::endl;
            // why does this maintain the sorted-ness of [stack,end)?
            // Because new_y points to the first element larger than old_y.
            // so when we swap them, we still maintain sorted order.
            std::swap(*old_y,*new_y);
            return true;
        }
       // std::cout << "Returning to top of loop" << std::endl;
    } 
    return false;
}

// motivated by an attempt to enumerate all possible perfect matchings
// in a graph. See also the pfaffian. To my knowledge, a new algorithm.
// Basic idea: we view the list as ((a,b),(c,d),...) pairs.
// when we consider (...(x,y)lmn...) we look in the set of elements
// lmn... to find a value z such that x<y<z.
// then recurse on (...(x,z)[this list])
//
// I think there's a better way. Let's look to Knuth...
// (Well, he does matching parens, but that's not quite the same.
template<typename iter>
bool next_match_first(const iter start, const iter end) {
    auto stack = end-2;
    do {
        auto y = *(--stack);
        auto x = *(--stack);

        // we use end here just to mean "invalid value"
        auto new_y = end;

        // from [stack,end) are ``unmatched vertices.''
        // Try to find a new one to partner with x 
        for (auto find_y = stack+2; find_y != end; ++find_y) {
            if (*find_y > x // valid partner for x
                    && *find_y > y // this lexicographically increases state
                    && (new_y == end || *find_y < *new_y)) { // valid to reassign 
                new_y = find_y;
            }
        
        }

        // if we suceeded in finding a new y for stack-1
        if (new_y != end) {
            ++stack; // push our old x back into the state
            std::swap(*new_y, *stack);
            ++stack;
            std::sort(stack+1,end);
            stack = end;
        }
        // if we couldn't start building a new state, and we've
        // popped the whole state, we're done.
        else if (stack == start) {
            return false;
        }
    } while(stack != end);
    // if we break, that means we've been able to reset our stack
    // (ie., we've built a new valid state)
    return true;
}





// at the end of the do-while loop, this leaves the range in the state
// [false,...,false,end)
// I'm not sure if this is from knuth.
template<typename iter>
bool next_subset(iter begin, iter end) {
    if (begin == end) { return false; }
    auto scanner = begin;
    while (scanner != end && *scanner) {
        *scanner = !(*scanner);
        ++scanner;
    }
    if (scanner != end) {
        *scanner = !(*scanner);
        return true;
    }
    return false;
}

// takes as input a combination of length t+2,
// exact copy of ``simple knuth''
// it works ``only'' for integer in [0,n], where array[t]=n, array[t+1]=0.
// (so for 8 choose 4, the input collection should be [0,1,2,3,8,0]).
template<class iter>
bool next_comb(iter start, iter end) {
    int j = 0;
    // we look for ``straight lines'', like 3456...
    // in doing so we reset it to 0123...
    while((*(start+j))+1 == *(start+(j+1))) {
        *(start+j) = j;
        ++j;
    }
    // if we get to the end in that process, that means we had 456780, so we're done.
    if (start+j>=end-2) {
        return false;
    }
    // otherwise, we got to the next point, which we increment.
    *(start+j)=*(start+j)+1;
    return true;
}


template<class iter>
unsigned length(iter begin, iter end) {
    unsigned l = 0;
    while(begin != end) {
        ++l;
        ++begin;
    }
    return l;
}

// this is supposedly faster, but is it?
template<class iter>
bool next_comb_static(iter start, iter end) {
    static const int l = length(start,end-2);
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

//
//
/// SCRAP
int retrieve(unsigned index, std::vector<int>& s) {
    unsigned counter = 0;
    int to_ret=-1;
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (counter == index) {
            to_ret = *it;
        }
        if (counter >= index) {
            if (it+1 != s.end()) {
                *it = *(it+1);
            }
        }
        ++counter;
    }
    return to_ret;
}

template<typename I, typename S>
void int_to_perm(int k, unsigned l, I a, S collection) {
    for (unsigned i = 0; i < l; ++i) {
        // we want the floor function here
        unsigned index = k/FACT[l-(i+1)];
        *a = retrieve(index,collection);
        ++a;
        k -= FACT[l-(i+1)]*index;
    }
}

// the goal of this function is the following:
// interpretting the sequence [begin, end) as the
// ith lexicographical permutation, transform it
// into the i+kth lexicographical permutation.
template<typename iter>
void int_to_perm(int k, iter begin, iter end) {
}

#endif
