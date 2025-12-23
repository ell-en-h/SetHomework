#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>

namespace test
{  
  struct InitializerListTest
  {
    InitializerListTest()
    {
      std::vector<int> values{20, 10, 30, 5, 14, 26, 40, 2, 7, 12, 19, 21, 28, 35, 50, 1, 6, 
        8, 11, 13, 17, 24, 27, 29};

      Set set{20, 10, 30, 5, 14, 26, 40, 2, 7, 12, 19, 21, 28, 35, 50, 1, 6, 
        8, 11, 13, 17, 24, 27, 29};
      
      for(int value: values)
        set.insert(value);

      set.erase(29);
      values.erase(std::find(values.begin(), values.end(), 29));
      
      for(int value: values)
        assertBool(set.contains(value), __LINE__, __FILE__);
      assertEqual(set.size(), values.size(), __LINE__, __FILE__);
      
      set.erase(2);
      values.erase(std::find(values.begin(), values.end(), 2));
      
      for(int value: values)
        assertBool(set.contains(value), __LINE__, __FILE__);
      assertEqual(set.size(), values.size(), __LINE__, __FILE__);

      set.erase(20);
      values.erase(std::find(values.begin(), values.end(), 20));

      for(int value: values)
        assertBool(set.contains(value), __LINE__, __FILE__);
      assertEqual(set.size(), values.size(), __LINE__, __FILE__);

      set.erase(14);
      values.erase(std::find(values.begin(), values.end(), 14));

      for(int value: values)
        assertBool(set.contains(value), __LINE__, __FILE__);
      assertEqual(set.size(), values.size(), __LINE__, __FILE__);
    }
  };

  static InitializerListTest InitializerListTest;
}