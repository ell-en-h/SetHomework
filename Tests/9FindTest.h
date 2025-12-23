#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>

namespace test
{
  struct FindTest
  {
    FindTest()
    {
      Set set{20, 10, 30, 5, 14, 26, 40, 2, 7, 12, 19, 21, 28, 35, 50, 1, 6, 
        8, 11, 13, 17, 24, 27, 29};
      std::vector<int> values(set.begin(), set.end());
      
      auto it = set.find(50);
      assertBool(it != set.end(), __LINE__, __FILE__);
      assertBool(*it == 50, __LINE__, __FILE__);
      assertBool(++it == set.end(), __LINE__, __FILE__);

      for(int value: values)
      {
        it = set.find(value);
        assertBool(it != set.end(), __LINE__, __FILE__);
        assertBool(*it == value, __LINE__, __FILE__);
      }

      it = set.find(1000);
      assertBool(it == set.end(), __LINE__, __FILE__);
    }
  };

  static FindTest findTest;
}