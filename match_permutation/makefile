all: driver match_perm_printer

driver: driver.cpp first_match.h second_match.h third_match.h
	clang++ -O3 -std=c++11 driver.cpp -o driver
match_perm_printer: match_perm_printer.cpp third_match.h
	clang++ -std=c++11 match_perm_printer.cpp -o match_perm_printer
clean:
	rm -f *.aux *.log enum driver match_perm_printer
