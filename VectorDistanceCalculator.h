#ifndef _VECTOR_DISTANCE_CALCULATOR
#define _VECTOR_DISTANCE_CALCULATOR

#include <vector>

namespace VectorCalculation {
	
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
	
	class EuclideanDistanceCalculator : public DistanceCalculator {
	public:
		/**
		 * @brief calculates the euclidean distance of two vectors.
		 * The euclidean equation is a specific case of minowski equation, where p is equals to 2,
		 * in order to save code we just use it. The euclidean distance is the square root of the sum of
		 * all the distances of two vectors cooardinates in the power of 2.
		 * 
		 * @param v1 the first vector.
		 * @param v2 the second vector.
		 * @return double The euclidean distance.
		 */
		double calculate(const std::vector<double>& v1, const std::vector<double>& v2) const override;
	};
	
	class ManhattanDistanceCalculator : public DistanceCalculator {
	public:
		/**
		 * @brief Calculates the manhattan distance of two vectors.
		 * the manhattan equation is a specific case of minowski equation,in order to save code we just use it.
		 * the manhattan distance is the sum of all the distances of two vectors cooardinates.
		 * 
		 * @param v1 the first vector.
		 * @param v2 the second vector.
		 * @return double The Manhattan distance.
		 */
		double calculate(const std::vector<double>& v1, const std::vector<double>& v2) const override;
	};
	
	class ChebyshevDistanceCalculator : public DistanceCalculator {
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
	
	class CanberraDistanceCalculator : public DistanceCalculator {
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
	
	class MinkowskiDistanceCalculator : public DistanceCalculator {
	private:
		int p;
	public:
		/**
		 * @brief Construct a new Minkowski Distance Calculator object
		 * 
		 * @param p The p argument for the Minkowski distance, by default p = 2.
		 */
		MinkowskiDistanceCalculator(const int& p = 2);
		
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
}

#endif // _VECTOR_DISTANCE_CALCULATOR
