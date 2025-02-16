# KNearestNeighbors in C++

## Overview
This is a C++ project that implements the KNearestNeighbors algorithm as a C++ server and a client to communicate with it. The server processes classification requests, while the client can send the data to be classified.

This project was done as part of a rolling university assignment.

## Features
- Implemented the KNearestNeighbors algorithm
- Supports various distance matrics such as Euclidean, Manhattan, and Chebyshev distances.
- Modular and optimized C++ implementation.
- Built using CMake for cross-platform compatibility.

## Installation
Ensure you have the following installed:

- **C++ Compiler** (GCC or Clang)
- **CMake** (Version 3.20+)
- **Docker** (if running in a container)

### Building from Source

1. Clone the repository:
   ```sh
   git clone https://github.com/NubPaws/KNearestNeighbors.git
   cd KNearestNeighbors
   ```
2. Build using CMake:
   ```sh
   cmake -S . -B bin && cmake --build bin
   ```
3. Run the server:
   ```sh
   ./bin/server 8080
   ```
4. Run the client:
   ```sh
   ./bin/client
   ```

## Running with Docker
1. Build the Docker image:
   ```sh
   docker build -t knn-server .
   ```
2. Run the container:
   ```sh
   docker run -p 8080:8080 knn-server
   ```

## Usage

- The server listens for client connections on port 8080.
- Clients can send data to be classified using the KNN algorithm.

## Project Structure

```
KNearestNeighbors/
├── src/
│   ├── calculations/        # KNN and distance calculations
│   ├── commands/            # Command processing
│   ├── ClientProgram.cpp    # Client application
│   ├── ServerProgram.cpp    # Server application
│   ├── Program.cpp          # Main program
├── include/                 # Header files
├── CMakeLists.txt           # CMake build configuration
├── Dockerfile               # Docker container setup
├── README.md                # Documentation
```

## Future Improvements

- Support for additional distance metrics
- Performance optimizations
- Improved client-server communication protocols

## Screenshots

*(Add images of running server, client interaction, and results here)*

---

Developed by Yuval & Rami.

## Exercises
### Exercise 1 - Vector Distance Calculation
#### Distance Calculations Changes
Distance calculations are now under the [Strategy Design Pattern](https://en.wikipedia.org/wiki/Strategy_pattern). That way we can create an instance of the `VectorDistance::Calculator` and pass to it a `VectorDistance::Calculator::Type` to select which calculation we want to do. We can also change the calculation method on the fly. It also makes adding a new type of vector distance calculation easier as we only need to add the new method into the tuple and it's string representation into the `VectorDistance::Calculator::TYPES` array.

The Euclidean and the Manhattan distance calculations are now subclasses of the Minkowski distance calculation class. They still have their own default constructors but they construct their super class with the related `p` value that they have.<br/>
The Euclidean with `p=2`.<br/>
The Manhattan with `p=2`.<br/>

#### Strategy Design Pattern
The idea in this case, for the strategy design pattern, was that we have a main class that should be used when a generic calculator is needed. That class is the `VectorDistance::Calculator` that receives the type of calculation you'd like to calculate (or not parameters at all). The class dynamically allocates space for the pointer of the specific vector calculation class.

### Exercise 2 - K Nearest Neighbors
#### K Nearest Neighbors
The KNN algorithm was implemented as it's own class. You can construct a `KNearestNegihbors` instance by passing to it a `VectorDataSet` instance and a `VectorDistance::Calculator::Type` for which calculation you'd like to use. You can also change the type on the fly using the `KNearestNeighbors::setDistanceType` method.<br/>
A `VectorDataSet` is constructed from a file. It uses a `CSVReader` to read a `.csv` file and then stores it as what we call a `DataEntry` which is just an `std::pair` where the first member is the vector and the second member is the name corresponding with that vector in the CSV file.

Using that knowledge the KNN algorithm `KNearestNeighbors::find` gets the vector that we want to match against and the `k` value. Then it goes over the VectorDataSet, swapping the `k` closest elements to be the first elements in the array. Afterwhich it runs over all of those first `k` elements, counting the different names that appear, and returning the one that is the most frequent.

To make the algorithm a bit faster all distances relative to the vector that is given into the function are pre-calculated and stored in a vector. Every swap in the dataset is followed by a swap in the distances' vector. The distances' vector is pretty big, therefore it is a must to pass it around as a reference to save on copying time.

#### Small Code Refactoring
Some functions (such as the function that checks if a string is double convertable and int convertable) were moved into separate namespaces. In the future, if they will fit as part of a class they will be moved to be part of a class, otherwise, they'll stay in a separate namespace - as to separate their logic.

We have also added a `Types.h` file that for now only has two declaration/using definitions as these were used quite a lot (and we wanted to save some time typing/abstract a bit of the implementation). In the future, we might give different names to types and even integral int types to make the code a bit more readable.

#### Makefile && Folder Structure Change
All files were moved into separate folders to make their separation a bit more logical. This has also made the need for a Makefile to be much more important. A Makefile was made and made to work with the multiple nested folders. For the Makefile construction we have followed the Makefile example [in this link](https://riptutorial.com/makefile/example/21376/building-from-different-source-folders-to-different-target-folders). There have been a few changes (regarding running the code on the Windows OS or running it on the Unix OS).

Regarding the Makefile, the code compiles using the C++11 standard. The Makefile is also simple to edit as if we were to add a new folder we only need to change the `DIRS` variable to add the new folder - adding new files does not require changes to the Makefile at all.. The Makefile also listens to changes not only in the `.cpp` files but also in their corresponding `.h` files.

### Exercise 3 - Server && Client
#### Socket Implementation
For this exercise we were only tasked with implementing a TCP socket connect. Therefore we made `TCPSocket` that is the base class for `TCPServer` and `TCPClient`. In the future if we'll need to implement a UDP socket we'll be able to create the Socket base class easily. The files were made each in their own file all under the network folder.
As per resources, the presentations and [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/) were of great assistance in the research of the topic. The idea of the implementation is to have a Server that is able to accept connections from Clients. That way we are abstracting the nitty gritty details of the socket library making it simple to establish the connection.

We have also added a `Packet` class that allows to pack the data from the user and the server and transfer them between one another. The idea for the packet is that when sending it or receiving we are are under the protocol of first receiving a `size_t` of the size of the actual data, and then we are receiving the data itself - which is just an array of `byte`s (`unsigned char`). In the future, if we want to transfer using JSon or XML we can just create a parser and then convert it to our Packet to transfer it back and forth.

#### Makefile && Folder Structure Change
The Makefile was made to export two executables `client.out` and `server.out`. That allows us to have two compilation units we can run. The folder structure was changed to also add a _network_ folder that stores our Socket and Socket related files.

### Ex4 - User Interface && Multithreading
#### Socket Refactoring
The socket class has been refactored to allow an easier implementation for the `SocketIO`.
The `acceptConnection()` function has been changed to return a TCPSocket object. In order to do so, a new constructor was added to `TCPSocket` which accepts file descriptor as an argument.
By doing so, after the call to `accept()` system call has been made, it is possible to create a `TCPSocket` object based on the returned file descriptor.
Since `acceptConnection()` returns `TCPSocket`, it is now possible to create `SocketIO` based on the returned value from `acceptConnection()`.

#### Input/Output Classes
We've created a `DefaultIO` interface that can read and write into different stream like objects. `StandardIO` extends the `DefaultIO` class and allows us to write into the standard output and read from the standard input. The `SocketIO` also extends the `DefaultIO` and allows us to write to a client connection and read from a client connect - in general it allows us to read and write between any two sockets, but in this specific implementation we are only writing to the client and reading from it.

#### Commands && Command Line Interface
We have implemented a `Command` base class to allow us to execute different commands that communicate between the client and the server. There is a separate class for one of each of the commands that are available for the user to choose. The commands are `UploadFileCommand`, `AlgorithmSettingsCommand`, `ClassifyDataCommand`, `DisplayResultsCommand`, and `DownloadResultsCommand`. Then the `CommandLineInterface`, shortened as CLI, handles calling the proper command based on the input that was received from the user, passing it the proper arguments using polymorphism.

#### Threads && Thead Pool Implementation
The fifth command has been made to execute on the separate thread.
For the server, in order to handle multiple clients at once, a `ThreadPool` class was made that stores the jobs that are needed to be done in a queue and executes them up to a max number of available threads. Each job is a client connect that needs to be handled. That way multiple clients can talk to the server at once, each has their own instance of a CLI. That way the data in the application is sort of seperated. This will enable us to not experience starvation, deadlocking and other problems that can appear when working with threads.

#### Folder Structure Changes
The `CSVReader` has been moved into the `utils/` folder to make it a bit more logical. The `io` folder has been filled with the `SocketIO`, `DefaultIO` and the `StandardIO` classes. A `threading/` folder has also been made to put in it threading related code and objects.
