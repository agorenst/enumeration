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

