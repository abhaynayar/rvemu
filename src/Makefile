all: rvemu

rvemu: main.o cpu.o memory.o bus.o
	g++ -o rvemu main.o cpu.o memory.o bus.o

main.o: main.cc
	g++ -c main.cc

cpu.o: cpu.cc
	g++ -c cpu.cc

bus.o: bus.cc
	g++ -c bus.cc

memory.o: memory.cc
	g++ -c memory.cc

clean:
	rm *.o rvemu

