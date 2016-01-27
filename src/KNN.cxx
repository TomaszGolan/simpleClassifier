#include "KNN.h"

//! loop over vector of points, fill neighbors, remove the farhest one
void fillNeighbors (const Point &p, std::multiset <Neighbor> &neighbors, 
                    const std::vector<Point> &points, const bool &flag)
{
  for (std::vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it)
  {
    neighbors.insert (Neighbor (p.distance (*it), flag));
    neighbors.erase (--neighbors.end());
  }
}

//! keep multiset of nNeighbors closest points with flag, fill multiset and 
bool KNN :: process (const Point &p) const
{
  std::multiset <Neighbor> neighbors; // set of closet neighbors
  // fill set with nNeighbors Points with infty distance
  for (unsigned int i = 0; i < nNeighbors; i++) neighbors.insert (Neighbor (std::numeric_limits<double>::max(), 0));
    
  fillNeighbors (p, neighbors, pointsA, true);  // fill neighbors list with learning sample A
  fillNeighbors (p, neighbors, pointsB, false); // fill neighbors list with learning sample B

  double scoreA = 0.0;
  double scoreB = 0.0;
    
  // loop over closest neighbors and count votes
  for (std::multiset<Neighbor>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    if (not (*it).first) return (*it).second; // distance = 0 -> the same point
    else if ((*it).second)     useWeights ? scoreA += 1.0 / (*it).first : scoreA++; // setA
    else if (not (*it).second) useWeights ? scoreB += 1.0 / (*it).first : scoreB++; // setB
                
  return scoreA > scoreB;
}
