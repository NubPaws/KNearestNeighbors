# Ran & Rami's Project

## Compilation
To compile the code run the following command.<br/>
`g++ Vector.cpp VectorDistanceCalculator.cpp Program.cpp`

Running the code on linux you should have an `./a.out` that you can run, on windows an `./a.exe`.

## Exercise 1 - Vector Distance Calculation
All distance calculation algorithms were placed under the namespace VectorDistanceCalculator. Each algorithm receives at least two `const std::vector<double>&` to do the calculations on. Each function uses the minimum of the two sizes of the vectors to run the calculations on - this is done to make sure that there is no index out of bounds.
### Euclidean distance
This distance is calculated using the Minkowski distance where `p=2`.
### Manhattan distance
This distance is calculated using the Minkowski distance where `p=1`.
### Minkowski distance
The default `p` value for this distance is set to be `2`.
