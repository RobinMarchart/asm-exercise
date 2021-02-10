
CXXFLAGS=-no-pie -std=c++11 -fno-pic -m32 -Wall
LDFLAGS=-L /usr/lib32 -m32
NASM=nasm
NASMFLAGS=-Xgnu -f elf32 -g -F dwarf -Wall

%.o: %.asm Makefile
	$(NASM) $(NASMFLAGS) $< -o $@

test: tests/registers.o tests/main.o taschenrechner/rechner.o Makefile
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o test tests/registers.o tests/main.o

tests/registers.o: tests/registers.cpp tests/registers.hpp tests/catch.hpp Makefile

tests/main.o: tests/main.cpp tests/catch.hpp Makefile

clean:
	rm test tests/main.o tests/registers.o

