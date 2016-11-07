// This is simply something that essentially increments
// a binary number represented as a sequence of bools.
// Very straightforward/naive.
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

