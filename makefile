all: driver SelfReduction

driver: enumeration.h driver.cpp
	g++ -O2 -Wall -std=c++0x driver.cpp -o driver

SelfReduction: SelfReduction.hs
	ghc SelfReduction


clean:
	rm -f *~ *.o *.hi SelfReduction driver
