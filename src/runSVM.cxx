#include "Classifier.h"
#include "KNN.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const unsigned int N_MIN  = 100; // minimum sample size
const unsigned int N_MAX  = 100; // maximum sample size
const unsigned int N_STEP =  25; // step for sample size

const vector <double> shifts = {0.0, -0.1, 0.1};

const string DIR = "svmResults/"; // output folder

// run SVM loop for separable or inseparable points for given shift
void runSVM (const bool separable, const double shift = 0.0);

int main ()
{
  for (auto &s : shifts) // loop over shifts
  {
    runSVM (true, s);  // separable points
    runSVM (false, s); // inseparable points
  }
       
  return 0;
}

// run SVM loop for separable or inseparable points for given shift
void runSVM (const bool separable, const double shift = 0.0)
{
  
}
