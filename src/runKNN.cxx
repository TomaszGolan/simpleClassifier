#include "Classifier.h"
#include "KNN.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const unsigned int N_MIN  =  10; // minimum sample size
const unsigned int N_MAX  = 100; // maximum sample size
const unsigned int N_STEP =  10; // step for sample size
const unsigned int K_MIN  =   1; // minimum no. of nearest neighbours
const unsigned int K_STEP =  10; // step for no. of nearest neighbours

const unsigned int N_REPEAT = 1000; // how many times repeat given configuration to obtain average score

const vector <double> shifts = {0.0, -0.1, 0.1};

const string DIR = "knnResults/"; // output folder

// run kNN loop for separable or inseparable points for given shift
void runKNN (const bool separable, const double shift = 0.0);

int main ()
{
  runKNN (true); return 0;
  
  for (auto &s : shifts) // loop over shifts
  {
    runKNN (true, s);  // separable points
    runKNN (false, s); // inseparable points
  }
       
  return 0;
}

// run kNN loop for separable or inseparable points for given shift
void runKNN (const bool separable, const double shift)
{ 
  // set flags based on arguments
  const string flagSep = separable ? "separable" : "inseparable";
  const string flagShf = shift == 0 ? "default" : (shift > 0 ? "distant" : "overlapped");
  
  // create all folders in the path "DIR/flagSep/flagShf"
  createPath (vector <string> ({DIR, flagSep, flagShf}));
    
  // files to save score for given configuration
  ofstream resultsFile ((DIR + "knn_" + flagSep + "_" + flagShf + ".dat").c_str());
  
  for (unsigned int n = N_MIN; n <= N_MAX; n += N_STEP) // sample size loop
  {
    for (unsigned int k = K_MIN; k <= n + 1; k += K_STEP) // no. of nearest neighbours loop
    {      
      // let me know what are you doing
      cout << "Running kNN (" << flagSep << ", " << flagShf << ") for N = " << n << ", k = " << k << " -> score = ";
      
      double score = 0;
      double repeat = 0; 
      
      while (++repeat <= N_REPEAT)
      {
      
        KNN knn (n, k, separable, shift); // create kNN for given configuration
      
        score += knn.run(); // get score

        // save learning samples, guessed points and not guessed points (only for first run)
        if (repeat == 1)
          knn.save ((DIR + flagSep + "/" + flagShf + "/" 
                     + "knn_" + to_string (n) + "_" + to_string (k) + "_" + flagSep + "_" + flagShf).c_str());      
      };
      
      score /= N_REPEAT;
      
      cout << score << "\n"; // print the score
      
      resultsFile << n << " " << k << " " << score << "\n"; // save the score
      
    } // no. of nearest neighbours loop end
    
    resultsFile << "\n"; // for gnuplot's splot
    
  } // sample size loop end
  
  resultsFile.close(); // close score file
}
