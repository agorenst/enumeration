driver: enumeration.h driver.cpp
	g++ -O2 -Wall -std=c++0x driver.cpp -o driver


clean:
	rm -f driver *~ *.o
