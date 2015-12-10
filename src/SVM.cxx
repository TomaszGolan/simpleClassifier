#include "SVM.h"
#include <limits>

using namespace std;

const double SVM::epsilon = 0.001; //!< numerical tolerance for KTT conditions

bool SVM::process (const Point &p) const
{
  return true;
}

//! update alphas in a loop (repeat until at least one was changed)
void SVM::learn (const char *book)
{
  bool isChanged = true; // flag to check if at least one alpha was changed
  
  while (isChanged and not (isChanged = false)) // loop until isChanged (and set initial value isChanged to false)
    for (unsigned int i = 0; i < N; i++)        // loop over alphas
      isChanged = updateAlpha (i) or isChanged; // call updateAlpha and update the flag
      
  printSurface();
}

//! if alpha violate KTT conditions try to update it with other alpha (loop until success)
bool SVM::updateAlpha (const unsigned int index)
{
  const double E2 = surfaceAt (index) - points[index].second; // the error on index-th training sample
  const double r2 = E2 * points[index].second;                // the error multiplied by y_index

  if ((r2 < -epsilon and alpha[index] < C) or (r2 > epsilon and alpha[index] > 0)) // KTT violated
    for (unsigned int i = 0; i < N; i++)       // loop over all points and try to update pair of alphas
      if (updateAlpha (i, index)) return true; // call success if alphas were updated
        
  return false; // call failure if it was impossible to update alphas or initial alpha does not violate KTT
}

//!< update given pair of alphas (true for success)
bool SVM::updateAlpha (const unsigned int i1, const unsigned int i2)
{
  if (i1 == i2) return false; // do not try update alpha with itself

  const double  s = points[i1].second * points[i2].second; // y_i1 * y_i2
  
  // low and high boundary for alpha value
  const double L = (s > 0) ? max (0.0, alpha[i2] + alpha[i1] - C) : max (0.0, alpha[i2] - alpha[i1]);
  const double H = (s > 0) ? min (  C, alpha[i2] + alpha[i1])     : min (  C, alpha[i2] - alpha[i1] + C);
    
  if (H - L < epsilon) return false; // do not try cases L == H

  const double E1 = surfaceAt (i1) - points[i1].second;    // the error on i1-th training sample
  const double E2 = surfaceAt (i2) - points[i2].second;    // the error on i2-th training sample 
  
  // scalar products
  const double k11 = points[i1].first * points[i1].first;
  const double k12 = points[i1].first * points[i2].first;
  const double k22 = points[i2].first * points[i2].first;
  
  // (vec x_i1 - vec x_i2)^2
  const double eta = k11 + k22 - 2.0 * k12;
      
  if (eta < epsilon) return false; // do not try duplicated points (eta == 0)
    
  double alpha2 = alpha[i2] + (E1 - E2) * points[i2].second / eta; // new alpha2 value
    
  // check if new alpha is within boundaries
  if (alpha2 < L) alpha2 = L; 
  else if (alpha2 > H) alpha2 = H;
  
  const double deltaAlpha2 = alpha2 - alpha[i2]; // the difference between old and new value of alpha2
  
  if (abs (deltaAlpha2) < epsilon) return false; // small change is not a change - skip it
  
  const double alpha1 = alpha[i1] + s * (alpha[i2] - alpha2); // new alpha1 value
  const double deltaAlpha1 = alpha1 - alpha[i1]; // the difference between old and new value of alpha1

  // thresholds
  const double b1 = b + E1 + deltaAlpha1 * k11 * points[i1].second + deltaAlpha2 * k12 * points[i2].second;
  const double b2 = b + E2 + deltaAlpha1 * k12 * points[i1].second + deltaAlpha2 * k22 * points[i2].second;

  // update surface
  wx += deltaAlpha1 * points[i1].first.getX() * points[i1].second +
        deltaAlpha2 * points[i2].first.getX() * points[i2].second; 
  
  wy += deltaAlpha1 * points[i1].first.getY() * points[i1].second + 
        deltaAlpha2 * points[i2].first.getY() * points[i2].second; 
  
  b = (b1 + b2) / 2.0;
  
  // update alpha
  alpha[i1] += s * (alpha[i2] - alpha2);
  alpha[i2] = alpha2;
    
  return 1;
}

//! loop over all alphas and calculate coefficients according to vec v = sum_i y_i * alpha_i * vec x_i
void SVM::updateSurface()
{
  for (unsigned int i = 0; i < N; i++)
  if (alpha[i] > epsilon)
  {
    const double ay = alpha[i] * points[i].second;
    wx +=  ay * points[i].first.getX();
    wy +=  ay * points[i].first.getY();
  }
}

//! check sign of a free parameter and print the surface in the form y = a*x + b
void SVM::printSurface () const 
{
  const double B = -b / wy;
  
  if (B > epsilon)
    std::cout << "\n\n y = " << - wx / wy << " * x + " << B << "\n\n";    
  else if (B < -epsilon)
    std::cout << "\n\n y = " << - wx / wy << " * x - " <<  -B << "\n\n";    
  else
    std::cout << "\n\n y = " << - wx / wy << " * x\n\n";    
}
