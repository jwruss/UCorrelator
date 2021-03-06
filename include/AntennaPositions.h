#ifndef _UCORRELATOR_ANTENNA_POSITIONS_H
#define _UCORRELATOR_ANTENNA_POSITIONS_H

#include "AnitaConventions.h" 
#include "stdint.h"

namespace UCorrelator
{
  /** This class keeps the positions of the antennas, and has some related methods. It is a singleton. */ 
  class AntennaPositions
  {

    static AntennaPositions * theInstance; 
    AntennaPositions(); 

    public: 
      /** Retrieve an instance */ 
      static const AntennaPositions * instance()
      { 
        if (__builtin_expect(!theInstance,0)) //apparently this call takes 2 percent of the runtime of everything!!! 
          theInstance = new AntennaPositions; 
        return theInstance;
      }

      /** Find closest N antennas to phi. Results put into closest, which should have sufficient room. Disallowed is a bitmap of antenna numbers that should be excluded. Returns number found (could be less than number requested if too many disallowed)*/
      int getClosestAntennas(double phi, int N, int * closest, uint64_t disallowed = 0) const; 

      /** antenna phi positions (degrees)*/
      double phiAnt[2][NUM_SEAVEYS]; 

      /** antenna r positions (m) */
      double rAnt[2][NUM_SEAVEYS]; 

      /** antenna z positions (m) */
      double zAnt[2][NUM_SEAVEYS]; 
  }; 
}


#endif
