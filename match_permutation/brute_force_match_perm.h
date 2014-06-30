#include <algorithm>

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
