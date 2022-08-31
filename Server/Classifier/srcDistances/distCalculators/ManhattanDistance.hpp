#ifndef MANHATTAND_H_DEFITIONS
#define MANHATTAND_H_DEFITIONS
#include "Server/Classifier/srcDistances/DistanceCalc.hpp"

/**
 * Responsible on the function of the project used Manhattan distance.
 */
class ManhattanDistance : public DistanceCalc {
public:
    /**
     *  override
     **/
    const double dist(const NPoint& p1, const NPoint& p2) const override;
    ManhattanDistance();
};

#endif