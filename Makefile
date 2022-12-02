# Choose the compiler.
CC=g++
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

build: VectorDistanceCalculator.o VectorDataSet.o KNearestNeighbors.o Program.o
	$(CC) VectorDistanceCalculator.o VectorDataSet.o KNearestNeighbors.o Program.o

# Make sure that when a header file is changed, the c file is recompiled
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

Program.o: Program.cpp
	$(CC) -c Program.cpp -o Program

clean:
	$(CLN) *.o a.out a.exe
