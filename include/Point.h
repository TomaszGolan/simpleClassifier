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

    //! possible positions: left side, inner circle, any, outer circle, right side
    enum Position {LEFT = -2, IN, ANY, OUT, RIGHT};
   
  private:
    
    double x; //!< x coordinate [-1, 1]
    double y; //!< y coordinate [-1, 1]
            
    static const PRNG random; //!< random number generator shared by all points
            
    static Position position; //!< defines the default position of new point
    
    static double shift; //!< positive shift makes space between two sets, negative makes them overlap
    
    Point (const double &x, const double &y) : x (x), y (y) {} //!< constructor of point with define coordinates
    
  protected:
        
    inline static void setPosition (const Position &p) { position = p; }          //!< set position given by user
    inline static void resetPosition () { position = ANY; }                       //!< set position to ANY
    inline static void switchPosition () { position = Position (-(int)position);} //!< reverse position, e.g. L->R
    
    Position getPosition (const bool &separable = true) const; //!< get true position
    
    inline static void setShift (const double x) { shift = x; } //!< set shift

  public:
    
    Point (); //!< constructor sets up random coordinates respect to position
        
    inline void print (std::ostream &os = std::cout) const { os << x << " " << y << "\n"; } //!< print point to ostream
            
    //! return euclidean distance from given point
    inline double distance (const Point& p) const { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y); }
};

#endif
