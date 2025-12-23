#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>

namespace test
{
  struct EraseIteratorTest
  {
    EraseIteratorTest()
    {
      
      std::vector<int> values{20, 10, 30, 5, 14, 26, 40, 2, 7, 12, 19, 21, 28, 35, 50, 1, 6, 
        8, 11, 13, 17, 24, 27, 29};
      Set set;

      for(std::size_t i = 0; i < values.size(); ++i)
      {
        std::vector<int> sorted_values(values.begin(), values.begin() + i + 1);
        std::sort(sorted_values.begin(), sorted_values.end());

        set.insert(values[i]);
        assertEqual(set.size(), sorted_values.size(), __LINE__, __FILE__);
        
        std::size_t k = 0;
        for(int value: set)
          assertEqual(value, sorted_values[k++], __LINE__, __FILE__);
      }

      while(!values.empty())
      {
        auto it = set.find(values.front());

        set.erase(it);
        values.erase(values.begin());
        assertEqual(set.size(), values.size(), __LINE__, __FILE__);
        
        auto sorted_values = values;
        std::sort(sorted_values.begin(), sorted_values.end());

        std::size_t k = 0;
        for(int value: set)
          assertEqual(value, sorted_values[k++], __LINE__, __FILE__);
      }
    }
  };

  static EraseIteratorTest eraseIteratorTest;
}