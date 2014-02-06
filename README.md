enumeration
===========

Efficient implementations of enumeration algorithms

Provides
========

It is often useful to enumerate through many combinatoric structures.
For instance, C++ provides a built-in function next\_permutation, which
allows for easy looping over all permutations of a given (sorted) sequence.

Partially inspired by my own research needs, and Knuth's volume 4, and
my own curiosity, I have been slowly implementing some choice selections
of his algorithms.
For instance, enumerating all combinations of [0,n) of size k.
There are many more such algorithms I'd like to implement, but it is slow going.

I have also my own algorithm, which is an interesting story as I carefully noted
my incremental improvements. The goal there is to enumerate "matching permutations",
a subset of permutations best explicated in the introductory materials in
"Matchgates Revisited".
The function it computes is fairly straightforward.
