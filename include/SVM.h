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

class SVM : public Classifier
{      
  private:
      
    bool process (const Point &p) const; //!< returns 0/1 if points is found to be in A/B set
    void learn (const char *book = NULL); //!< learn classifier, pass file name if already learned
          
  public:
  
    //! constructor calls Classifier constructor
    SVM (const unsigned int &N, const bool separable = true, const double shift = 0.0)
      : Classifier (N, separable, shift) {}
};

#endif

