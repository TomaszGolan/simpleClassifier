#include "Classifier.h"
#include "KNN.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;

const unsigned int N_MIN  = 50; // minimum sample size
const unsigned int N_MAX  = 100; // maximum sample size
const unsigned int N_STEP =  10; // step for sample size
const unsigned int K_MIN  =  10; // minimum no. of nearest neighbors
const unsigned int K_STEP =  10; // step for no. of nearest neighbors

const string DIR = "knnResults/"; // output folder

// run kNN loop for separable or inseparable points for given shift
void runKNN (const bool separable, const double shift = 0.0);

// create a single dir
void createDir (boost::filesystem::path dir);

// create folder structure for the results
void createDirs ();

int main ()
{   
  createDirs();
  
  runKNN (true);  // separable points
  runKNN (false); // inseparable points
  runKNN (true, -0.1);  // separable points
  runKNN (false, -0.1); // inseparable points
  runKNN (true, 0.1);  // separable points
  runKNN (false, 0.1); // inseparable points

  return 0;
}

// create a single dir
void createDir (boost::filesystem::path dir)
{
  if (not boost::filesystem::exists (dir))
    if (not boost::filesystem::create_directory (dir)) // try to create folder
    {
      // stop program if folder could not be created
      cout << "\n\nERROR: could not create " << dir << "\n\n";
      exit (1); 
    }  
}

// create folder structure for the results
void createDirs ()
{
  // list of folders to create
  vector <boost::filesystem::path> dirs = {
                          DIR, DIR + "/separable", DIR + "/inseparable", 
                          DIR + "/separable/default/", DIR + "/separable/distant/", DIR + "/separable/overlapped/",
                          DIR + "/inseparable/default/", DIR + "/inseparable/distant/", DIR + "/inseparable/overlapped/"
                        };
  
  // loop over folders
  for (auto &d : dirs) createDir (d);
}

// run kNN loop for separable or inseparable points for given shift
void runKNN (const bool separable, const double shift)
{ 
  const string flagSep = separable ? "separable" : "inseparable";
  const string flagShf = shift == 0 ? "default" : (shift > 0 ? "distant" : "overlapped");
    
  // files to save score for given configuration
  ofstream resultsFile ((DIR + "knn_" + flagSep + "_" + flagShf + ".dat").c_str());
  
  for (unsigned int n = N_MIN; n <= N_MAX; n += N_STEP) // sample size loop
  {
    for (unsigned int k = K_MIN; k <= n; k += K_STEP) // no. of nearest neighbours loop
    {
      cout << "Running kNN (" << flagSep << ", " << flagShf << ") for N = " << n << ", k = " << k << " -> score = ";
      
      KNN knn (n, k, separable, shift); // create kNN for given configuration
      
      const double score = knn.run(); // get score
      
      cout << score << "\n";
      
      resultsFile << n << " " << k << " " << score << "\n";
      
      // save learning samples, guessed points and not guessed points
      knn.save ((DIR + flagSep + "/" + flagShf + "/" 
                 + "knn_" + to_string (n) + "_" + to_string (k) + "_" + flagSep + "_" + flagShf).c_str());      
      
    } // sample size loop end
    
    resultsFile << "\n"; // for gnuplot's splot
    
  } // no. of nearest neighbors loop end
  
  resultsFile.close(); // close score file
}
