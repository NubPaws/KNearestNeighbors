# Choose the compiler.
CC := g++
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN := del
	F_EXT := exe
else
	CLN := rm
	F_EXT := out
endif

BUILD_FILES  = VectorDistance.o
BUILD_FILES += VectorDataSet.o
BUILD_FILES += StringValidator.o
BUILD_FILES += KNearestNeighbors.o
BUILD_FILES += CSVReader.o
BUILD_FILES += CommandLineArguments.o

build: $(BUILD_FILES) Program.o
	$(CC) $(BUILD_FILES) Program.o

# Build the algs foldfer
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

# Clean command
clean:
	$(CLN) *.o a.out a.exe

# Exercise 2 test.
ex2_test: build
	./a.$(F_EXT) 3 ./datasets/iris/iris_classified.csv MAN
