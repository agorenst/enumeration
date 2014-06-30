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

