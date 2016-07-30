all: driver SelfReduction permutation

permutation: permutation.cpp
	clang++ -O3 -Wall -std=c++11 permutation.cpp -o permutation

driver: enumeration.h driver.cpp
	g++ -O2 -Wall -std=c++0x driver.cpp -o driver

SelfReduction: SelfReduction.hs
	ghc SelfReduction


clean:
	rm -f *~ *.o *.hi SelfReduction driver permutation
