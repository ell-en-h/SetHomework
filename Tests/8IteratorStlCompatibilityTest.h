#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>
#include <type_traits>

namespace test
{  
  struct IteratorStlCompatibilityTest
  {
    IteratorStlCompatibilityTest()
    {
      Set set{5, 2, 3, 4, 1, 10, 20};
      std::vector<int> values{5, 2, 3, 4, 1, 10, 20};
      std::sort(values.begin(), values.end());
      std::size_t k = 0;
      
      for(int value: set)
        assertEqual(value, values[k++], __LINE__, __FILE__);

      auto it = std::find(set.begin(), set.end(), 30);
      assertBool(it == set.end(), __LINE__, __FILE__);
    }
  };

  static IteratorStlCompatibilityTest iteratorStlCompatibilityTest;
}