/**
 * @brief support vector machine
 * 
 * @author TG
 * @date 2015
 * 
*/

#ifndef SVM_H
#define SVM_H

#include "Classifier.h"
#include <algorithm>

class SVM : public Classifier
{      
  private:
    
    static const double epsilon; //!< numerical tolerance
    
    const unsigned int N; //!< number of samples (total = A + B)

    const double C; //!< free parameter (boundary for alpha)

    std::vector <std::pair<Point, int>> points; //!< Point + y in {-1, 1}

    double wx, wy, b;           //!< surface coefficient wx * x + wy * y - b = 0    
    std::vector <double> alpha; //!< Lagrange multipliers    
    
    bool process (const Point &p) const;  //!< returns 0/1 if points is found to be in A/B set
    void learn (const char *book = NULL); //!< learn classifier, pass file name if already learned
 
    bool updateAlpha (const unsigned int index);                     //!< update given alpha value (true if updated)
    bool updateAlpha (const unsigned int i1, const unsigned int i2); //!< update given pair of alphas (true for success)
    void updateSurface();                                            //!< update wx and wy coefficients 
    inline double surfaceAt (const unsigned int index) const         //!< return the value of surface at given point
      {return wx * points[index].first.getX() + wy * points[index].first.getY() - b;}
      
    void printSurface () const; //!< print the final surface as y = ax + b
       
  public:
  
    //! constructor calls Classifier constructor (initialize surface coefficient and alpha as 0)
    SVM (const unsigned int &N, const bool separable = true, const double shift = 0.0)
      : Classifier (N, separable, shift), N (2*N), C (1.0), wx (0.0), wy (0.0), b (0.0)
    {
      // just for convenience store all points in one vector as pairs (point, value)
      for (const auto &p : pointsA) points.emplace_back (p, 1);
      for (const auto &p : pointsB) points.emplace_back (p, -1);
     
      // fill alpha values with 0 (so sum_i alpha_i * y_i = 0)
      alpha.resize (points.size(), 0.0); 
       
      learn ();
    }
};

#endif

