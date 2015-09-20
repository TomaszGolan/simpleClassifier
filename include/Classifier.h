/**
 * @brief Abstract class for classifiers
 * 
 * @author TG
 * @date 2015
 * 
*/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "Point.h"
#include <vector>

class Classifier
{  
  private:
  
    const bool separable; 
  
    //! convert process result to Point::Position
    Point::Position proceed (const Point &p) const
      { return process (p) ? (separable ? Point::LEFT : Point::IN) : (separable ? Point::RIGHT : Point::OUT); }
  
    virtual bool process (const Point &p) const = 0; //!< returns true/false if points is found to be in A/B set
    
    virtual void learn (const char *book = NULL) {}; //!< learn classifier, pass filename if already learned

  protected:
    
    std::vector <Point> pointsA; //!< first learning sample
    std::vector <Point> pointsB; //!< second learning samples    
    
  public:
  
    Classifier (const unsigned int &N, const bool separable = true); //!< constructor fills learning samples
    
    //! check is point is reconstructed correctly
    inline bool isReconstructed (const Point &p) const { return p.getPosition (separable) == proceed (p); }
    
    void save (std::ostream &osA = std::cout, std::ostream &osB = std::cout) const; //!< save learning samples
};

#endif
