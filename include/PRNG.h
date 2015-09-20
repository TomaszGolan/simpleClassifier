/**
 * @brief Pseudorandom number generator
 * 
 * @author TG
 * @date 2015
 * 
*/

#ifndef PRNG_H
#define PRNG_H

#include <random>
#include <memory>
#include <cfloat>

class PRNG
{
  private:
  
    std::unique_ptr <std::mt19937> engine; //!< use mersenne twister engine
    std::unique_ptr <std::uniform_real_distribution <double>> distribution00; //!< real number distribution (x,y)
    std::unique_ptr <std::uniform_real_distribution <double>> distribution01; //!< real number distribution (x,y]
    std::unique_ptr <std::uniform_real_distribution <double>> distribution10; //!< real number distribution [x,y)
    std::unique_ptr <std::uniform_real_distribution <double>> distribution11; //!< real number distribution [x,y]
          
  public:
  
    //! constructor initialize engine with random seed and sets up the range of number given by user
    PRNG (const double &min, const double &max)
    { 
      // inititate engine
      std::random_device rd;
      engine.reset (new std::mt19937 (rd()));
      
      //set up distributions      
      distribution00.reset (new std::uniform_real_distribution <double> (std::nextafter (min, DBL_MIN), max));
      distribution01.reset (new std::uniform_real_distribution <double> (std::nextafter (min, DBL_MIN),
                                                                         std::nextafter (max, DBL_MAX)));
      distribution10.reset (new std::uniform_real_distribution <double> (min, max));
      distribution11.reset (new std::uniform_real_distribution <double> (min, std::nextafter (max, DBL_MAX)));
    }
    
    //! return random number from the range (min, max) (defined in constructor)
    inline double generate00 () const { return (*distribution00)(*engine); }
    //! return random number from the range (min, max] (defined in constructor)
    inline double generate01 () const { return (*distribution01)(*engine); }
    //! return random number from the range [min, max) (defined in constructor)
    inline double generate10 () const { return (*distribution10)(*engine); }
    //! return random number from the range [min, max] (defined in constructor)
    inline double generate11 () const { return (*distribution11)(*engine); }
};

#endif
