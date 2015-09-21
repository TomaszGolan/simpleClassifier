#include "Classifier.h"
#include "KNN.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const unsigned int N_MIN  = 100; // minimum sample size
const unsigned int N_MAX  = 500; // maximum sample size
const unsigned int N_STEP =  50; // step for sample size
const unsigned int K_MIN  =  10; // minimum no. of nearest neighbors
const unsigned int K_STEP =  10; // step for no. of nearest neighbors

const string DIR = "knnResults/"; // output folder

// run kNN loop for separable or inseparable points
void runKNN (const bool &sep);

int main ()
{ 
  runKNN (true);
  runKNN (false);
       
  return 0;
}

// run kNN loop for separable or inseparable points
void runKNN (const bool &sep)
{ 
  string flag;
  
  if (sep) flag = "separable";
  else flag = "inseparable";
    
  ofstream resultsFile ((DIR + "knn_" + flag + ".dat").c_str()); // files to save score for given configuration
  
  for (unsigned int n = N_MIN; n < N_MAX; n += N_STEP) // sample size loop
  {
    for (unsigned int k = K_MIN; k < n; k += K_STEP) // no. of nearest neighbors loop
    {
      cout << "Running kNN (" << flag << ") for N = " << n << ", k = " << k << " -> score = ";
      
      KNN knn (n, k, sep); // create kNN for given configuration
      
      const double score = knn.run(); // get score
      
      cout << score << "\n";
      
      resultsFile << n << " " << k << " " << score << "\n";
      
      // save learning samples, guessed points and not guessed points
      knn.save ((DIR + flag + "/knn_" + to_string (n) + "_" + to_string (k) + "_" + flag + ".dat").c_str());      
      
    } // sample size loop end
    
    resultsFile << "\n"; // for gnuplot's splot
    
  } // no. of nearest neighbors loop end
  
  resultsFile.close(); // close score file
}
