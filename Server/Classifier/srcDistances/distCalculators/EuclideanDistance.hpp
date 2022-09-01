#ifndef EUCLIDEAND_H_INCLUDED
#define EUCLIDEAND_H_INCLUDED

#include "Server/Classifier/srcDistances/DistanceCalc.hpp"
/**
 * Responsible on the function of the project used Euclidean distance.
 */
class EuclideanDistance : public DistanceCalc {
public:
    /**
     *  override
     **/
    const double dist(const NPoint& p1, const NPoint& p2) const override;
    EuclideanDistance();
    ~EuclideanDistance() override = default;
};

#endif