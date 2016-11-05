#include <algorithm>

// are all the elements in sorted order?
// This seems very over-specified...
template<class iter>
bool first_perm(const iter start, const iter end) {
    for (int i = 0; start+i != end; ++i) {
        if (*(start+i) >= *(start+1+i)) {
            return false;
        }
    }
    return true;
}

template<class iter>
bool is_valid_match_perm(iter begin, iter end) {
    // empty case
    if (begin == end) { return true; }

    // make sure n is even
    if (std::distance(begin, end) % 2 != 0) {
        return false;
    }

    for (; begin != end; begin += 2) {
        auto next_start = begin + 2;
        if (next_start != end) {
            if (*next_start < *begin) {
                return false;
            }
        }
        auto partner = begin + 1;
        if (*partner < *begin) {
            return false;
        }
    }
    return true;
}

template<class iter>
bool simple_match(const iter start, const iter end) {
    do {
        std::next_permutation(start, end);
    } while(!is_valid_match_perm(start, end));
    if (first_perm(start, end)) {
        return false;
    }
    return true;
}

// motivated by an attempt to enumerate all possible perfect matchings
// in a graph. See also the pfaffian. To my knowledge, a new algorithm.
// Basic idea: we view the list as ((a,b),(c,d),...) pairs.
// when we consider (...(x,y)lmn...) we look in the set of elements
// lmn... to find a value z such that x<y<z.
// then recurse on (...(x,z)[this list])
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
                    // this lexicographically increases state
                    && *find_y > y
                    // valid to reassign?
                    && (new_y == end || *find_y < *new_y)) { 
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
        if (new_y != end) {
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
        // This loop is really just a ``left-shift''.
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
            // This loop is really just a single iteration of selection sort.
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

