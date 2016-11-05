
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

