# Yuval & Rami's Project

- [Yuval \& Rami's Project](#yuval--ramis-project)
	- [Compilation](#compilation)
- [Exercise 1 - Vector Distance Calculation](#exercise-1---vector-distance-calculation)
	- [Distance Calculations Changes](#distance-calculations-changes)
	- [Strategy Design Pattern](#strategy-design-pattern)
- [Exercise 2 - K Nearest Neighbors](#exercise-2---k-nearest-neighbors)
	- [K Nearest Neighbors](#k-nearest-neighbors)
	- [Small Code Refactoring](#small-code-refactoring)
	- [Makefile \&\& Folder Structure Change](#makefile--folder-structure-change)
- [Exercise 3 - Server \&\& Client](#exercise-3---server--client)
	- [Socket Implementation](#socket-implementation)
	- [Makefile \&\& Folder Structure Change](#makefile--folder-structure-change-1)

## Compilation
To compile the code run the `make` command in the same directory the `Makefile` is located in.
Running the code on linux you should have an `./a.out` that you can run, on windows an `a.exe`.

# Exercise 1 - Vector Distance Calculation
## Distance Calculations Changes
Distance calculations are now under the [Strategy Design Pattern](https://en.wikipedia.org/wiki/Strategy_pattern). That way we can create an instance of the `VectorDistance::Calculator` and pass to it a `VectorDistance::Calculator::Type` to select which calculation we want to do. We can also change the calcualtion method on the fly. It also makes adding a new type of vector distance calculation easier as we only need to add the new method into the tuple and it's string representation into the `VectorDistance::Calculator::TYPES` array.

The Euclidean and the Manhattan distance calculations are now subclasses of the Minkowski distance calculation class. They still have their own default constructors but they construct their super class with the related `p` value that they have.<br/>
The Euclidean with `p=2`.<br/>
The Manhattan with `p=2`.<br/>

## Strategy Design Pattern
The idea in this case, for the strategy design pattern, was that we have a main class that should be used when a generic calculator is needed. That class is the `VectorDistance::Calculator` that receives the type of calculation you'd like to calculate (or not paremeters at all). The class dynamically allocates space for the pointer of the specific vector calculation class.

# Exercise 2 - K Nearest Neighbors
## K Nearest Neighbors
The KNN algorithm was implemented as it's own class. You can construct a `KNearestNegihbors` instance by passing to it a `VectorDataSet` instance and a `VectorDistance::Calculator::Type` for which calculation you'd like to use. You can also change the type on the fly using the `KNearestNeighbors::setDistanceType` method.<br/>
A `VectorDataSet` is constructed from a file. It uses a `CSVReader` to read a `.csv` file and then stores it as what we call a `DataEntry` which is just an `std::pair` where the first member is the vector and the second member is the name corresponding with that vector in the CSV file.

Using that knowledge the KNN algorithm `KNearestNeighbors::find` gets the vector that we want to match against and the `k` value. Then it goes over the VectorDataSet, swapping the `k` closest elements to be the first elements in the array. Afterwhich it runs over all of those first `k` elements, counting the different names that appear, and returning the one that is the most frequent.

To make the algorithm a bit faster all distances relative to the vector that is given into the function are pre-calculated and stored in a vector. Every swap in the dataset is followed by a swap in the distances' vector. The distances' vector is pretty big, therefore it is a must to pass it around as a reference to save on copying time.

## Small Code Refactoring
Some functions (such as the function that checks if a string is double convertable and int convertable) were moved into seperate namespaces. In the future, if they will fit as part of a class they will be moved to be part of a class, otherwise, they'll stay in a seperate namespace - as to seperate their logic.

We have also added a `Types.h` file that for now only has two declartion/using definitions as thise were used quite a lot (and we wanted to save some time typing/abstract a bit of the implementation). In the future, we might give different names to types and even integral int types to make the code a bit more readable.

## Makefile && Folder Structure Change
All files were moved into seperate folders to make their seperation a bit more logical. This has also made the need for a Makefile to be much more important. A Makefile was made and made to work with the multiple nested folders. For the Makefile construction we have followed the Makefile example [in this link](https://riptutorial.com/makefile/example/21376/building-from-different-source-folders-to-different-target-folders). There have been a few changes (regarding running the code on the Windows OS or running it on the Unix OS).

Regarding the Makefile, the code compiles using the C++11 standard. The Makefile is also simple to edit as if we were to add a new folder we only need to change the `DIRS` variable to add the new folder - adding new files does not require changes to the Makefile at all.. The Makefile also listens to changes not only in the `.cpp` files but also in their corresponding `.h` files.

# Exercise 3 - Server && Client
## Socket Implementation
For this exercise we were only tasked with implementing a TCP socket connect. Therefore we made `TCPSocket` that is the base class for `TCPServer` and `TCPClient`. In the future if we'll need to implement a UDP socket we'll be able to create the Socket base class easily.
As per resources, the presentations and [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/) were of great assistance in the research of the topic. The idea of the implementation is to have a Server that is able to accept connections from Clients. That way we are abstracting the nitty gritty details of the socket library making it simple to establish the connection.

We have also added a `Packet` class that allows to pack the data from the user and the server and transfer them between one another. The idea for the packet is that when sending it or receiving we are are under the protocol of first receiving a `size_t` of the size of the actual data, and then we are receiving the data itself - which is just an array of `byte`s (`unsigned char`). In the future, if we want to transfer using JSon or XML we can just create a parser and then convert it to our Packet to transfer it back and forth.

## Makefile && Folder Structure Change
The Makefile was made to export two executables `client.out` and `server.out`. That allows us to have two compilation units we can run. The folder structure was changed to also add a _network_ folder that stores our Socket and Socket related files.
