# Ran & Rami's Project

### Compilation
To compile the code run the following command.
`g++ Vector.cpp VectorDistanceCalculator.cpp Program.cpp`

Running the code on linux you should have an `./a.out` that you can run, on windows an `./a.exe`.

### Exercise 1 - Vector Distance Calculation
The algorithms were placed in their own namespace.
Both the Euclidean algorithm and the Manhattan algorithm use the Minkowski algorithm. Each one is using them with a different value of p (2 and 1 accordingly).
There is a `Vector` class where you can access each of it's members using the `[]` operator. That way we can iterate over the vector while still remembering it has x, y, and z coordinates.
