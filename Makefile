enumerator: enumerator.cpp combination.h
	clang++ -Wall -std=c++11 -O2 enumerator.cpp -o enumerator

clean:
	rm -f *.o *~ enumerator
