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
  
    const bool separable; //!< separable point or not
    
    const unsigned int nTrain; //!< size of the training set
    const unsigned int nTest;  //!< size of the testing set
        
    std::vector <Point> pointsS; //!< points guessed correctly
    
    std::vector <Point> pointsF; //!< points not guessed correctly
  
    //! convert process result to Point::Position
    Point::Position proceed (const Point &p) const
      { return process (p) ? (separable ? Point::LEFT : Point::IN) : (separable ? Point::RIGHT : Point::OUT); }
  
    //! check is point is reconstructed correctly
    inline bool isReconstructed (const Point &p) const { return p.getPosition (separable) == proceed (p); }
    
    //! print chosen vector of points to given ostream
    inline void print (const std::vector <Point> &points, std::ostream &os) const
      { for (auto &p : points) p.print (os); }

    virtual bool process (const Point &p) const = 0; //!< returns true/false if points is found to be in A/B set
    
    virtual void learn (const char *book = NULL) {}; //!< learn classifier, pass file name if already learned

  protected:
    
    std::vector <Point> pointsA; //!< first learning sample
    std::vector <Point> pointsB; //!< second learning samples    
    
  public:
  
    //! constructor fills learning samples
    Classifier (const unsigned int nTrain, const unsigned int nTest, const bool separable = true, const double shift = 0);

    double run (); //!< run classifier and return score

    void print (std::ostream &osA = std::cout, std::ostream &osB = std::cout,
                std::ostream &osS = std::cout, std::ostream &osF = std::cout) const; //!< save/print learning samples
               
    void save (const std::string base) const; //!< save learning samples
};

#endif
