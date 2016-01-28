#include "Classifier.h"
#include "KNN.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const unsigned int N_TEST   = 100;  // the size of testing samples
const unsigned int N_REPEAT = 1000; // number of repetition per configuration

const unsigned int N_MIN  =   5; // minimum sample size
const unsigned int N_MAX  = 100; // maximum sample size
const unsigned int N_STEP =  10; // step for sample size
const unsigned int K_MIN  =   5; // minimum no. of nearest neighbours
const unsigned int K_STEP =  10; // step for no. of nearest neighbours

const vector <double> shifts = {0.0, -0.1, 0.1};

const string DIR = "knnResults/"; // output folder

// run kNN loop for separable or inseparable points for given shift
void runKNN (const bool separable, const double shift = 0.0, const bool useWeights = false);

int main ()
{ 
  for (auto &s : shifts) // loop over shifts
  {
    runKNN (true, s, false);  // separable points w/o weights
    runKNN (false, s, false); // inseparable points w/o weights
    runKNN (true, s, true);  // separable points with weights
    runKNN (false, s, true); // inseparable points with weights
  }
       
  return 0;
}

// run kNN loop for separable or inseparable points for given shift
void runKNN (const bool separable, const double shift, const bool useWeights)
{ 
  // set flags based on arguments
  const string flagSep = separable ? "separable" : "inseparable";
  const string flagShf = shift == 0 ? "default" : (shift > 0 ? "distant" : "overlapped");
  const string flagWgt = useWeights ? "weighted" : "unweighted";
  
  // create all folders in the path "DIR/flagSep/flagShf"
  createPath (vector <string> ({DIR, flagWgt, flagSep, flagShf}));
    
  // files to save score for given configuration
  ofstream resultsFile ((DIR + "knn_" + flagSep + "_" + flagShf + "_" + flagWgt + ".dat").c_str());
  
  for (unsigned int n = N_MIN; n <= N_MAX; n += N_STEP) // sample size loop
  {
    for (unsigned int k = K_MIN; k <= n; k += K_STEP) // no. of nearest neighbours loop
    {      
      // let me know what are you doing
      cout << "Running kNN (" << flagSep << ", " << flagShf << ", " << flagWgt << ") "
            << "for N = " << n << ", k = " << k << " -> score = ";
      
      double score = 0;
      double N = 0;
      
      while (N++ <= N_REPEAT)
      {
        KNN knn (n, N_TEST, k, separable, shift, useWeights); // create kNN for given configuration
        score += knn.run(); // get score

        // save learning samples, guessed points and not guessed points (only for first run)
        if (N == 1)
          knn.save ((DIR + "/" + flagWgt + "/" + flagSep + "/" + flagShf + "/"
               + "knn_" + to_string (n) + "_" + to_string (k) + "_" + flagSep + "_" + flagShf + "_" + flagWgt).c_str());      
      }
      
      score /= N_REPEAT; // average score
            
      cout << score << "\n"; // print the score
      
      resultsFile << n << " " << k << " " << score << "\n"; // save the score
      
    } // no. of nearest neighbours loop end
    
    resultsFile << "\n"; // for gnuplot's splot
    
  } // sample size loop end
  
  resultsFile.close(); // close score file
}
