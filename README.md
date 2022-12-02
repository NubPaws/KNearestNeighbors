# Ran & Rami's Project

## Compilation
You can compile the code using the `make` command.
Running the code on linux you should have an `./a.out` that you can run, on windows an `./a.exe`.

## Exercise 2 - K Nearest Neighbors
Distance calculations moved into a more OOP style layout. Each distance is now a class and we can pass it around between functions as instances now. That is useful for us when we calculate the KNN. That way we can also change the algorithm the KNN uses to measure distance on the fly.

## Exercise 1 - Vector Distance Calculation
All distance calculation algorithms were placed under the namespace VectorDistanceCalculator. Each algorithm receives at least two `const std::vector<double>&` to do the calculations on. Each function uses the minimum of the two sizes of the vectors to run the calculations on - this is done to make sure that there is no index out of bounds.
### Euclidean distance
This distance is calculated using the Minkowski distance where `p=2`.
### Manhattan distance
This distance is calculated using the Minkowski distance where `p=1`.
### Minkowski distance
The default `p` value for this distance is set to be `2`.
