
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


// this is supposedly faster, but is it?
template<class iter>
bool next_comb_static(iter start, iter end) {
    static const int l = distance(start,end-2);
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


template<typename ITER>
void printer(ITER begin, ITER end) {
    for (; begin != end; ++begin) {
        cout << *begin << " ";
    }
    cout << endl;
}

// return t elements in {0...n}
// Algorithm L from fascile 3a.
// (Algorithm T is an advanced extension of this)
void visit_all_combinations(int n, int t) {
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
        printer(begin(c), begin(c)+t);
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
