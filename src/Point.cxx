#include "Point.h"

const PRNG Point::random = PRNG (0.0, 1.0); //!< initialize random number generator

const double Point::radius = 1.0; //!< initilize radius

Point::Position Point::position = ANY; //!< initialize position as any

//! generate random (x,y) pair matches given conditions
Point :: Point ()
{ 
  if (position == ANY) // any point from rectangle [2R, 2R]
  {
      x = 4.0 * radius * (random.generate01() - 0.5);
      y = 4.0 * radius * (random.generate01() - 0.5);
      return;
  }
  
  const double alpha = 2.0 * M_PI * random.generate10(); // random angle
    
  switch (position)
  {
    case LEFT: // point from left cricle with center at (-R, -R), variate a little bit 
    {
      const double R = radius * sqrt (random.generate11());
      x = variate (R) * cos (alpha) - radius;
      y = variate (R) * sin (alpha) - radius;
      break;
    }
    case RIGHT: // point from right circle with center at (R. R), variate a little bit 
    {
      const double R = radius * sqrt (random.generate11());
      x = variate (R) * cos (alpha) + radius;
      y = variate (R) * sin (alpha) + radius;
      break;
    }
    case IN: // point from inner ring, radius from [0.5R, R]
    {
      const double R = (0.5 * sqrt (random.generate11()) + 0.5) * radius;
      x = R * cos (alpha);
      y = R * sin (alpha);
      break;
    }
    case OUT: // point from outer ring, radius from [1.5R, R]
    {
      const double R = (0.5 * sqrt (random.generate11()) + 1.5) * radius;
      x = R * cos (alpha);
      y = R * sin (alpha);
      break;
    }
    default: break;
  }
}

//! check LEFT vs RIGHT if separable, or IN vs OUT
Point::Position Point::getPosition (const bool &separable) const
{  
  if (separable)
    return distance (Point (radius, radius)) > distance (Point (-radius, -radius)) ? Point::LEFT : Point::RIGHT;
  
  return distance (Point (0.0, 0.0)) < 1.25 * radius ? Point::IN : Point::OUT;
}
