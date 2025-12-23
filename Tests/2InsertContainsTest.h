#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>

namespace test
{
  struct InsertContainsTest
  {
    InsertContainsTest()
    {
      Set set1;
      assertBool(!set1.contains(10), __LINE__, __FILE__);
      
      set1.insert(10);
      set1.insert(5);
      set1.insert(6);
      set1.insert(20);

      assertBool(set1.contains(10), __LINE__, __FILE__);
      assertBool(set1.contains(5), __LINE__, __FILE__);
      assertBool(set1.contains(6), __LINE__, __FILE__);
      assertBool(set1.contains(20), __LINE__, __FILE__);
      assertEqual(set1.size(), 4, __LINE__, __FILE__);
      set1.insert(20);
      assertEqual(set1.size(), 4, __LINE__, __FILE__);

      assertBool(!set1.contains(7), __LINE__, __FILE__);

      std::vector<int> values{10, 5, 6, 20, 3, 2, 1, 30, 40, 50, 60, 100, 54, 12};
      
      Set set2;
      for(int value: values)
        set2.insert(value);
      
      for(int value: values)
        assertBool(set2.contains(value), __LINE__, __FILE__);

      assertEqual(set2.size(), values.size(), __LINE__, __FILE__);
      set2.insert(54);
      assertEqual(set2.size(), values.size(), __LINE__, __FILE__);

      assertBool(!set2.contains(7), __LINE__, __FILE__);
    }
  };

  static InsertContainsTest insertFindTest;
}