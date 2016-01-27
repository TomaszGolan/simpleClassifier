/**
 * @brief k nearest neighbors
 * 
 * @author TG
 * @date 2015
 * 
*/

#ifndef KNN_H
#define KNN_H

#include "Classifier.h"
#include <set>

//! <distance, isFirstSet>
typedef std::pair <const double, const bool> Neighbor; 

class KNN : public Classifier
{      
  private:
    
    const unsigned int nNeighbors; //!< number of nearest neghbors to look for

    const bool useWeights; //!< votes weight depends on the distance if true
  
    bool process (const Point &p) const; //!< returns 0/1 if points is found to be in A/B set
          
  public:
  
    //! constructor calls Classifier constructor and sets up number of nearest neighbors
    KNN (const unsigned int nTrain, const unsigned int nTest, const unsigned int k, const bool separable = true,
         const double shift = 0.0, const bool useWeights = false)
         : Classifier (nTrain, nTest, separable, shift), nNeighbors (k), useWeights (useWeights) {}
};

#endif
