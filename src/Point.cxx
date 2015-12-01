#include "Point.h"

const PRNG Point::random = PRNG (0.0, 1.0); //!< initialize random number generator

Point::Position Point::position = ANY; //!< initialize position as any
double Point::shift = 0.0; //!< initialize shift as 0

//! generate random (x,y) pair matches given conditions
Point :: Point ()
{ 
  
  if (position == ANY)
  {
    x = 2.0 * (random.generate11() - 0.5); // random x from the whole range
    y = 2.0 * (random.generate11() - 0.5); // random y from the whole range
  }  
  else if (position == IN or position == OUT)
  {
    const double alpha = 2.0 * M_PI * random.generate10(); // random angle
    // R in [0, 0.5] for inner circle and [0.5, 1.0] for outer one
    const double radius = position == IN ? sqrt ((0.5 - shift) * random.generate11()) :
                                           sqrt ((0.5 - shift) * random.generate11() + 0.5 + shift);
    x = radius * cos (alpha);
    y = radius * sin (alpha);
  }
  else
  {
    const double u = random.generate11();
    x = 2.0 * sqrt(u) - 1.0;
    
    if (position == LEFT) // y > x
    {
      x *= -1.0;
      y = x + shift + (1.0 - x - shift) * random.generate11();
    }
    else y = -1.0 + (x - shift + 1.0) * random.generate11();
  }
}

//! check LEFT vs RIGHT if separable, or IN vs OUT
Point::Position Point::getPosition (const bool &separable) const
{  
  if (separable) return y > x ? LEFT : RIGHT;
  
  return distance (Point (0.0, 0.0)) < 0.5 ? Point::IN : Point::OUT;
}
