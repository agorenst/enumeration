#include <algorithm>

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
