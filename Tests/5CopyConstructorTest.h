#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>

namespace test
{  
  struct CopyConstructorTest
  {
    CopyConstructorTest()
    {
      Set set1{5, 2, 3, 4, 1, 10, 20};
      Set set2 = set1;

      assertEqual(set1.size(), set2.size(), __LINE__, __FILE__);

      set1.insert(30);
      assertBool(set1.contains(30), __LINE__, __FILE__);
      assertBool(!set2.contains(30), __LINE__, __FILE__);
      assertEqual(set1.size(), set2.size()+1, __LINE__, __FILE__);
    }
  };

  static CopyConstructorTest copyConstructorTest;
}