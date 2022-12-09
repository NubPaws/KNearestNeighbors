#ifndef _VECTOR_DISTANCE
#define _VECTOR_DISTANCE

#include <vector>
#include <string>

#include "Types.h"

namespace VectorDistance {
	
	class DistanceCalculator;
	
	/**
	 * @brief Calculator is a class using the strategy design pattern. The idea is that
	 * you choose a type in this class and call the distance calculation function through
	 * this class using the operator().
	 * That way we can pass the type we want and create the calculator based on the type
	 * that we passed around.
	 * This also allows changed to the calculation function on the fly.
	 */
	class Calculator {
	public:
		/**
		 * @brief The enum that we will use, using the class definition to force explicit
		 * convertions between a Type and an int. The Type::Empty refers to the size of
		 * types we have (that is why it is at the end of the enum). We can use this to
		 * iterate over the array of types that we have.
		 */
		enum class Type : size_t {
			Euclidean, Manhattan, Chebyshev, Canberra, Minkowski, Empty
		};
		/**
		 * @brief Get the Calculator::Type based on a string passed to it.
		 * 
		 * @param name The name of the type - should be refered from the TYPES string array
		 * at the top of the code.
		 * @return VectorDistance::Calculator::Type The type infered from the string that was passed
		 * or the type Type::Empty if no type was matched.
		 */
		static Type getType(const std::string& name);
	private:
		static const std::string TYPES[];
		
	private:
		/* 
		 * The reason we have a DistanceCalculator pointer and not a reference or a variable
		 * is to allow us to have the polymorphism that we require. We have it as a pointer
		 * so that whenever we need to move or copy the class we can do so easily. Not having
		 * to worry about two instanced of Calculator having the same pointer to DistanceCalculation.
		 */
		DistanceCalculator *distCalc;
		Type type;
		
	public:
		/**
		 * @brief Default constructor for a new Calculator object
		 */
		Calculator();
		
		/**
		 * @brief Construct a new Calculator object
		 * 
		 * @param type The type of distance calculation the user would prefer.
		 */
		Calculator(const Type& type);
		
		/*
		 * The following 5 coonstructor are for the RAII design.
		 * We have a copy constructor, a copy assignment operator, a move constructor,
		 * and a move assignment operator.
		 * We also have a destructor that has the goald to remove the data of the
		 * DistanceCalculation pointer we have.
		 */
		
		Calculator(const Calculator& other);
		Calculator& operator=(const Calculator& other);
		
		Calculator(Calculator&& other) noexcept;
		Calculator& operator=(Calculator&& other) noexcept;
		
		~Calculator();
		
		/**
		 * @brief Sets the calculation method based on the type that was given to it.
		 * 
		 * @param type A Calculator::Type that chooses which type we'll have.
		 * @param p If there is a need for a p parameter we can set it as well.
		 */
		void set(const Type& type, const int& p = 2);
		
		/**
		 * @brief Operator to make the Calculator be callable as a function.
		 * 
		 * @param v1 The first vector to do the calculation with.
		 * @param v2 The second vector to do the calculation with.
		 * @return double THe distance based on the method chosen and the two vectors given.
		 * returns -1 in case there was no method chosen (which should raise eyebrows because
		 * a distance cannot be negative in our field).
		 */
		double operator()(const std::vector<double>& v1, const std::vector<double>& v2) const;
	};
	
	class DistanceCalculator {
	public:
		/**
		 * @brief Calculates the distance between the two vectors given to it.
		 * 
		 * @param v1 The first vector in the calculation.
		 * @param v2 The second vector in the calculation.
		 * @return double The specified distance between the two vectors.
		 */
		virtual double calculate(const std::vector<double>& v1, const std::vector<double>& v2) const = 0;
		
		/**
		 * @brief Calls the calculate function with the same arguments given to it.
		 * 
		 * @param v1 The first vector in the calculation.
		 * @param v2 The second vector in the calculation.
		 * @return double The specified distance between the two vectors.
		 */
		double operator()(const std::vector<double>& v1, const std::vector<double>& v2) const;
	};
	
	class ChebyshevCalculator : public DistanceCalculator {
	public:
		/**
		 * @brief Calculates the Chebyshev distance of two vectors.
		 * The Chebyshev distance is the maximum of the distances in each one of the axis.
		 * 
		 * @param v1 The first vector.
		 * @param v2 The second vector.
		 * @return double THe Chebyshev distance.
		 */
		double calculate(const std::vector<double>& v1, const std::vector<double>& v2) const override;
	};
	
	class CanberraCalculator : public DistanceCalculator {
	public:
		/**
		 * @brief Calculates the Canberra distance of the two vectors.
		 * The Canberra distance is the sum of |pi-qi|/(|pi|-|qi|) where pi and qi are the values of vectors
		 * p and q in the i-th axis.
		 * 
		 * @param v1 The first vector.
		 * @param v2 The second vector.
		 * @return The Canberra distance of the two vectors.
		 */	
		double calculate(const std::vector<double>& v1, const std::vector<double>& v2) const override;
	};
	
	class MinkowskiCalculator : public DistanceCalculator {
	private:
		int p;
	public:
		/**
		 * @brief Construct a new Minkowski Distance Calculator object
		 * 
		 * @param p The p argument for the Minkowski distance, by default p = 2.
		 */
		MinkowskiCalculator(const int& p = 2);
		
		/**
		 * @brief calculates the minkowski distance of two vectors.
		 * the minkowski equation calculate the sum of of |v1[i]-v2[i]| in the power of p
		 * where v1, v2 represents the vecotrs, and the i represnt the axis(i = 0 is x,i = i is y and so on)  
		 * then it returns the sum in the power of 1/p
		 *
		 * @param v1 the first vector.
		 * @param v2 the second vector.
		 * @param p the order of the distnace.
		 * @return double The Minkowski distnace
		*/
		double calculate(const std::vector<double>& v1, const std::vector<double>& v2) const override;
		
		void setP(const int& p);
		int getP() const;
	};
	
	class EuclideanCalculator : public MinkowskiCalculator {
	public:
		/**
		 * @brief Construct a new Euclidean Calculator object passing the constructor
		 * of the Minkowski class with the parameter p = 2.
		 */
		EuclideanCalculator();
	};
	
	class ManhattanCalculator : public MinkowskiCalculator {
	public:
		/**
		 * @brief Construct a new Manhattan Calculator object passing the constructor
		 * of the Minkowski class with the parameter p = 1.
		 */
		ManhattanCalculator();
	};
	
	
}

#endif // _VECTOR_DISTANCE_ALGS
