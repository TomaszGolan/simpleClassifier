#include "Classifier.h"

//! fill samples A/B by LEFT/RIGHT points or IN/OUT (circle), depends if user wants separable points or not
Classifier :: Classifier (const unsigned int &N, const bool separable) : separable (separable)
{
  // set Point::position for first set
  if (separable) Point::setPosition (Point::LEFT);
  else Point::setPosition (Point::IN);
  
  pointsA.resize (N); // default constructor sets point randomly according to Point::position
  
  Point::switchPosition(); // change position, LEFT -> RIGHT, IN -> OUT
  
  pointsB.resize (N); // fill second set
  
  Point::resetPosition(); // reset position, so points are randomized from whole rectangle
  
  learn();
}

//! print pointsA to osA, and pointsB to osB
void Classifier :: save (std::ostream &osA, std::ostream &osB) const
{
  for (std::vector<Point>::const_iterator it = pointsA.begin(); it != pointsA.end(); ++it) (*it).print (osA);
  for (std::vector<Point>::const_iterator it = pointsB.begin(); it != pointsB.end(); ++it) (*it).print (osB);
}

