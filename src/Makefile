all: crvemu

crvemu: main.o cpu.o
	g++ -o crvemu main.o cpu.o

main.o: main.cc
	g++ -c main.cc

cpu.o: cpu.cc
	g++ -c cpu.cc

clean:
	rm *.o crvemu
