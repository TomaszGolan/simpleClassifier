#include "Classifier.h"
#include "KNN.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// run kNN algorithm for given sample size, number of nearest neighbors for separable case or not
double runKNN (const unsigned int &N, const unsigned int &k, const bool &sep);

int main ()
{ 
  ofstream fileSep   ("knnResults/knn.separable");   // results for separable case
  ofstream fileInSep ("knnResults/knn.inseparable"); // results for inseparable case
  
  for (unsigned int n = 100; n <= 500; n += 50) // sample size loop
  {
    for (unsigned int k = 10; k <= n; k += 10) // no. of nearest neighbors loop
    {
      cout << "Running kNN for N = " << n << ", k = " << k << "...\n";
      
      fileSep   << n << " " << k << " " << runKNN (n, k, true) << "\n";
      fileInSep << n << " " << k << " " << runKNN (n, k, false) << "\n";      
    } // sample size loop end
    
    fileSep << "\n";   // for gnuplot's splot
    fileInSep << "\n"; // for gnuplot's splot
  } // no. of nearest neighbors loop end
  
  // close files
  fileSep.close();
  fileInSep.close();
       
  return 0;
}

// run kNN algorithm for given sample size, number of nearest neighbors for separable case or not
double runKNN (const unsigned int &N, const unsigned int &k, const bool &sep)
{  
  KNN knn (N, k, sep); // initialize classifier
  
  string base = "knnResults/knn_" + to_string (N) + "_" + to_string (k); // common string for files name
  
  // add proper tag
  if (sep) base += "_separable";
  else base += "_inseparable";
  
  // open files
  ofstream fileSetA ((base + ".A").c_str());
  ofstream fileSetB ((base + ".B").c_str());
  ofstream fileGood ((base + ".good").c_str());
  ofstream fileBad ((base + ".bad").c_str());
  
  // save learning samples
  knn.save (fileSetA, fileSetB);
  
  unsigned int score = 0;
  
  for (unsigned int i = 0; i < N; i++) // points loop
  {
    Point p; // create random point
        
    if (knn.isReconstructed (p)) // if guessed correctly
    {
      p.print (fileGood); // save as guessed point
      score++;
    }
    else p.print (fileBad); // save as not guessed point
  }
  
  // close files
  fileSetA.close();
  fileSetB.close();
  fileGood.close();
  fileBad.close();
  
  return (double) score / (double) N; // return score
}
