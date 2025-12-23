#pragma once
#include "../Set.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

namespace test
{
  struct TimeLimitTest
  {
    TimeLimitTest()
    {
      Set set;

      auto start = std::chrono::system_clock::now();
      
      for(std::size_t i = 0; i < 1000000; ++i)
      {
        set.insert(i);
      }
      
      auto end = std::chrono::system_clock::now();

      using namespace std::chrono_literals;
      assertBool(end-start < 1000ms, __LINE__, __FILE__);
    }
  };

  static TimeLimitTest timeLimitTest;
}