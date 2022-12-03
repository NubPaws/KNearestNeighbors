#include "KNearestNeighbors.h"
#include "VectorDataSet.h"



class KNearestNeighbors {
private:
    VectorCalculation::VectorDataSet dataset;
    VectorCalculation::DistanceCalculator &distance;
public:
    KNearestNeighbors(VectorCalculation::VectorDataSet dataset, VectorCalculation::DistanceCalculator distance){
        dataset = dataset;
        distance = distance;
    }

    std::string find(std::size_t k) const;
private:

};