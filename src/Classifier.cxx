#include "Classifier.h"
#include <fstream>

//! fill samples A/B by LEFT/RIGHT points or IN/OUT (circle), depends if user wants separable points or not
Classifier :: Classifier (const unsigned int nTrain, const unsigned int nTest, const bool separable, const double shift)
                          : separable (separable), nTrain (nTrain), nTest (nTest)
{
  Point::setShift (shift);
  
  // set Point::position for first set
  if (separable) Point::setPosition (Point::LEFT);
  else Point::setPosition (Point::IN);
  
  pointsA.resize (nTrain); // default constructor sets point randomly according to Point::position
  
  Point::switchPosition(); // change position, LEFT -> RIGHT, IN -> OUT
  
  pointsB.resize (nTrain); // fill second set
  
  Point::resetPosition(); // reset position, so points are randomized from whole rectangle  
}

//! print pointsA to osA, and pointsB to osB
void Classifier :: print (std::ostream &osA, std::ostream &osB, std::ostream &osS, std::ostream &osF) const
{
  print (pointsA, osA);
  print (pointsB, osB);
  print (pointsS, osS);
  print (pointsF, osF);  
}

//! open files and save vectors of points
void Classifier :: save (const std::string base) const
{
  std::ofstream fileA ((base + "_A.dat").c_str()); // first learning samples
  std::ofstream fileB ((base + "_B.dat").c_str()); // second learning samples
  std::ofstream fileS ((base + "_S.dat").c_str()); // correctly guessed points
  std::ofstream fileF ((base + "_F.dat").c_str()); // points not guessed
  
  print (fileA, fileB, fileS, fileF); // print all vectors to files
  
  // close files
  fileA.close();
  fileB.close();
  fileS.close();
  fileF.close();
}

//! generate N points, check if reconstructed correctly and save to proper vector
double Classifier :: run ()
{
  for (unsigned int i = 0; i < nTest; i++) // points loop
  {
    Point p; // create random point
        
    if (isReconstructed (p)) pointsS.push_back (p); // guessed correctly
    else pointsF.push_back (p);
  }
  
  return (double)pointsS.size() / (double)nTest;
}
