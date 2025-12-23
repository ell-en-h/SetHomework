#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>

namespace test
{
  struct UpperAndLowerBoundsTest
  {
    UpperAndLowerBoundsTest()
    {
      Set set{20, 10, 30, 5, 14, 26, 40, 2, 7, 12, 19, 21, 28, 35, 50, 1, 6, 
        8, 11, 13, 17, 24, 27, 29};

      auto it = set.upper_bound(36);
      assertEqual(*it, 40, __LINE__, __FILE__);

      it = set.upper_bound(0);
      assertEqual(*it, 1, __LINE__, __FILE__);

      it = set.upper_bound(20);
      assertEqual(*it, 21, __LINE__, __FILE__);      

      it = set.upper_bound(10);
      assertEqual(*it, 11, __LINE__, __FILE__);

      it = set.upper_bound(50);
      assertBool(it == set.end(), __LINE__, __FILE__);

      it = set.upper_bound(100);
      assertBool(it == set.end(), __LINE__, __FILE__);

      //////////////////////////////////////////////////////////////////////////
      
      it = set.lower_bound(36);
      assertEqual(*it, 40, __LINE__, __FILE__);
      
      it = set.lower_bound(0);
      assertEqual(*it, 1, __LINE__, __FILE__);

      it = set.lower_bound(20);
      assertEqual(*it, 20, __LINE__, __FILE__);      

      it = set.lower_bound(10);
      assertEqual(*it, 10, __LINE__, __FILE__);
      
      it = set.lower_bound(50);
      assertEqual(*it, 50, __LINE__, __FILE__);

      it = set.lower_bound(100);
      assertBool(it == set.end(), __LINE__, __FILE__);
    }
  };

  static UpperAndLowerBoundsTest upperAndLowerBoundsTest;
}