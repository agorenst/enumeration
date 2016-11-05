Enumeration
===========

This contains simple implementations of algorithms that list out ("enumerate") certain combinatoric structures.
Examples include:
* All permutations of [0,n).
* Computing the i-th permutation of [0,n)
* All s-t combinations of [0,n).
And more to come.
This is very much inspired by Knuth's volume 4a.

Usage
=====

Things are still a bit in progress, but the ultimate goal is to allow the following features:
* A set of headers to be included in any C++ project.
* An "enumerator" program that can take flags and integer parameters to output a particular combinatoric structure sequence.
** An example would be something like ".\enumerator perm 8", and it would output all permutations of [0,8).
* Benchmarking certain algorithms, to make sure the solutions I'm providing aren't being completely silly.

Applications
============

1) Testing: I hope to use these generated objects to easily exhaustively test other combinatoric algorithms.
For instance, enumerating all permutations of 10 elements isn't ridiculous, and may help test sorting routines.
2) Education: I think these algorithms are really neat. I think Knuth is on my side.
They're not very well-covered in traditional algorithms textbooks.
Maybe as I fill out the algorithm list I will be able to start having a cohesive exposition of my own.

Todo
====
I'm trying to use the "issues" feature on Github to track this.
Refer to that, please.
