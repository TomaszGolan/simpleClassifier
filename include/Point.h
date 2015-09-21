/**
 * @brief Simple random 2D points handler
 * 
 * @author TG
 * @date 2015
 * 
*/

#ifndef RANDOM_POINT_H
#define RANDOM_POINT_H

#include "PRNG.h"
#include <iostream>

class Classifier;

class Point
{ 
  friend class Classifier; //!< Classifier need to change Point::position during samples initialization
  
  public:

    //! possible positions: left circle, inner circle, any circle, outer circle, right circle
    enum Position {LEFT = -2, IN, ANY, OUT, RIGHT};
   
  private:
    
    double x; //!< x coordinate
    double y; //!< y coordinate
        
    //! use to variate radius a little (do not want to have perfect circles)
    inline double variate (const double &x) const { return x * random.generate11() * exp ((x-radius) * (x-radius)); }
    
    static const PRNG random; //!< random number generator shared by all points
    
    static const double radius; //!< base circle radius
        
    static Position position; //!< defines the circle point should be randommized from
    
    Point (const double &x, const double &y) : x (x), y (y) {} //!< constructor of point with define coordinates
    
  protected:
        
    inline static void setPosition (const Position &p) { position = p; }          //!< set position given by user
    inline static void resetPosition () { position = ANY; }                       //!< set position to ANY
    inline static void switchPosition () { position = Position (-(int)position);} //!< reverse position, e.g. L->R
    
    Position getPosition (const bool &separable = true) const; //!< get the closest circle

  public:
    
    Point (); //!< constructor sets up radnom coordinates respect to position
        
    inline void print (std::ostream &os = std::cout) const { os << x << " " << y << "\n"; } //!< print point to ostream
            
    //! return euclidean distance from given point
    inline double distance (const Point& p) const { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y); }
};

#endif
