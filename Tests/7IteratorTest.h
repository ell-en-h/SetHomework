#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>
#include <type_traits>

namespace test
{  
  struct IteratorTest
  {
    // Although std::set has bidirectional iterator, you are allowed
    // to implement just forward iterator and the tests will pass.
    IteratorTest() 
    {
      Set set{5, 2, 3, 4, 1, 10, 20};
      std::vector<int> values{5, 2, 3, 4, 1, 10, 20};
      std::sort(values.begin(), values.end());

      Set::iterator it = set.begin();
      assertEqual(*it, 1, __LINE__, __FILE__);
      assertBool(it == set.begin(), __LINE__, __FILE__);
      assertBool(!(it != set.begin()), __LINE__, __FILE__);
      std::size_t k = 0;

      for(; it != set.end(); ++it)
        assertEqual(*it, values[k++], __LINE__, __FILE__);

      it = set.begin();
      assertBool(std::is_const<std::remove_reference_t<decltype(*it)>>::value, __LINE__, __FILE__); // This means that *iterator must be of a type const int&

      assertEqual(*(it++), 1, __LINE__, __FILE__);
      assertEqual(*it, 2, __LINE__, __FILE__);
      assertEqual(*(++it), 3, __LINE__, __FILE__);
      assertEqual(*it, 3, __LINE__, __FILE__);
    }
  };

  static IteratorTest iteratorTest;
}