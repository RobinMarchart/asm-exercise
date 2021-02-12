
CXXFLAGS=-no-pie -std=c++11 -fno-pic -m32 -Wall
LDFLAGS=-L /usr/lib32 -m32 -no-pie
NASM=nasm
NASMFLAGS=-Xgnu -f elf32 -g -F dwarf -Wall

all: test taschenrechner_test

%.o: %.asm Makefile
	$(NASM) $(NASMFLAGS) $< -o $@

test: tests/registers.o tests/main.o taschenrechner/rechner.o Makefile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o test tests/registers.o tests/main.o taschenrechner/rechner.o

tests/registers.o: tests/registers.cpp tests/registers.hpp tests/catch.hpp Makefile

tests/main.o: tests/main.cpp tests/catch.hpp Makefile

clean:
	rm -f test tests/main.o tests/registers.o taschenrechner/rechner.o taschenrechner_test

taschenrechner_test: tests/registers.o tests/main.o taschenrechner/rechner.o Makefile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o taschenrechner_test tests/registers.o tests/main.o taschenrechner/rechner.o

.PHONY: clean all
