# Ran & Rami's Project

- [Ran \& Rami's Project](#ran--ramis-project)
	- [Compilation](#compilation)
	- [Exercise 1 - Vector Distance Calculation](#exercise-1---vector-distance-calculation)
		- [Euclidean distance](#euclidean-distance)
		- [Manhattan distance](#manhattan-distance)
		- [Minkowski distance](#minkowski-distance)
	- [Exercise 2 - K Nearest Neighbors](#exercise-2---k-nearest-neighbors)
		- [K Nearest Neighbors](#k-nearest-neighbors)
		- [Small Code Refactoring](#small-code-refactoring)
		- [Makefile \&\& Folder Structure Change](#makefile--folder-structure-change)
		- [Distance Calculations Changes](#distance-calculations-changes)

## Compilation
To compile the code run the `make` command in the same directory the `Makefile` is located in.
Running the code on linux you should have an `./a.out` that you can run, on windows an `a.exe`.

## Exercise 1 - Vector Distance Calculation
All distance calculation algorithms were placed under the namespace VectorDistanceCalculator. Each algorithm receives at least two `const std::vector<double>&` to do the calculations on. Each function uses the minimum of the two sizes of the vectors to run the calculations on - this is done to make sure that there is no index out of bounds.
### Euclidean distance
This distance is calculated using the Minkowski distance where `p=2`.
### Manhattan distance
This distance is calculated using the Minkowski distance where `p=1`.
### Minkowski distance
The default `p` value for this distance is set to be `2`.

## Exercise 2 - K Nearest Neighbors
### K Nearest Neighbors
The KNN algorithm was implemented as it's own class. You can construct a `KNearestNegihbors` instance by passing to it a `VectorDataSet` instance and a `VectorDistance::Calculator::Type` for which calculation you'd like to use. You can also change the type on the fly using the `KNearestNeighbors::setDistanceType` method.
A `VectorDataSet` is constructed from a file. It uses a `CSVReader` to read a `.csv` file and then stores it as what we call a `DataEntry` which is just an `std::pair` where the first member is the vector and the second member is the name corresponding with that vector in the CSV file.
Using that knowledge the KNN algorithm `KNearestNeighbors::find` gets the vector that we want to match against and the `k` value. Then it goes over the VectorDataSet, swapping the `k` closest elements to be the first elements in the array. Afterwhich it runs over all of those first `k` elements, counting the different names that appear, and returning the one that is the most frequent.
To make the algorithm a bit faster all distances relative to the vector that is given into the function are pre-calculated and stored in a vector. Every swap in the dataset is followed by a swap in the distances' vector. The distances' vector is pretty big, therefore it is a must to pass it around as a reference to save on copying time.
### Small Code Refactoring
Some functions (such as the function that checks if a string is double convertable and int convertable) were moved into seperate namespaces. In the future, if they will fit as part of a class they will be moved to be part of a class, otherwise, they'll stay in a seperate namespace - as to seperate their logic.
We have also added a `Types.h` file that for now only has two declartion/using definitions as thise were used quite a lot (and we wanted to save some time typing/abstract a bit of the implementation). In the future, we might give different names to types and even integral int types to make the code a bit more readable.
### Makefile && Folder Structure Change
All files were moved into seperate folders to make their seperation a bit more logical. This has also made the need for a Makefile to be much more important. A Makefile was made and made to work with the multiple nested folders. For the Makefile construction we have followed the Makefile example [in this link](https://riptutorial.com/makefile/example/21376/building-from-different-source-folders-to-different-target-folders). There have been a few changes (regarding running the code on the Windows OS or running it on the Unix OS).
Regarding the Makefile, the code compiles using the C++11 standard. The Makefile is also simple to edit as if we were to add a new folder we only need to change the `DIRS` variable to add the new folder - adding new files does not require changes to the Makefile at all.. The Makefile also listens to changes not only in the `.cpp` files but also in their corresponding `.h` files.
### Distance Calculations Changes
Distance calculations are now under the [Strategy Design Pattern](https://en.wikipedia.org/wiki/Strategy_pattern). That way we can create an instance of the `VectorDistance::Calculator` and pass to it a `VectorDistance::Calculator::Type` to select which calculation we want to do. We can also change the calcualtion method on the fly. It also makes adding a new type of vector distance calculation easier as we only need to add the new method into the tuple and it's string representation into the `VectorDistance::Calculator::TYPES` array.
