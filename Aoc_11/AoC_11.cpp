//
//  main.cpp
//  Aoc_11
//
//  Created by Neurosion on 12/11/22.
//

#include <iostream>
#include <fstream>
#include <deque>
#include <array>
#include <functional>
#include <algorithm>

namespace
{
  std::array<std::function<long long (long long)>, 8> monkey_op = {
    { [](long long old) { return old * 2;   },
      [](long long old) { return old * old; },
      [](long long old) { return old + 6;   },
      [](long long old) { return old + 2;   },
      [](long long old) { return old * 11;  },
      [](long long old) { return old + 7;   },
      [](long long old) { return old + 1;   },
      [](long long old) { return old + 5;   }
    }
  };

  std::array<std::function<int (long long)>, 8> monkey_test = {
    { [](long long n) { return n % 11 == 0 ? 1 : 4; },
      [](long long n) { return n % 19 == 0 ? 7 : 3; },
      [](long long n) { return n % 7  == 0 ? 0 : 5; },
      [](long long n) { return n % 17 == 0 ? 6 : 2; },
      [](long long n) { return n % 3  == 0 ? 1 : 7; },
      [](long long n) { return n % 5  == 0 ? 0 : 4; },
      [](long long n) { return n % 13 == 0 ? 5 : 2; },
      [](long long n) { return n % 2  == 0 ? 3 : 6; },
    }
  };

  long long mod = 11 * 19 * 7 * 17 * 3 * 5 * 13 * 2;
}

int main(int argc, const char * argv[]) {
  for (int part_i = 1; part_i <= 2; ++part_i) {
    std::array<std::deque<long long>, 8> monkey_items = {
      { { 98, 70, 75, 80, 84, 89, 55, 98 },
        { 59                             },
        { 77, 95, 54, 65, 89             },
        { 71, 64, 75                     },
        { 74, 55, 87, 98                 },
        { 90, 98, 85, 52, 91, 60         },
        { 99, 51                         },
        { 98, 94, 59, 76, 51, 65, 75     } }
    };
    
    std::array<long long, 8> monkey_inspections = {};
    
    for (int round = 0; round < (part_i == 1 ? 20 : 10000); ++round) {
      for (int monkey_i = 0; monkey_i < monkey_items.size(); ++monkey_i) {
        while(!monkey_items[monkey_i].empty()) {
          monkey_inspections[monkey_i]++;
          long long new_item = monkey_op[monkey_i](monkey_items[monkey_i].front());
          if (part_i == 1) {
            new_item /= 3;
          }
          else {
            new_item %= mod;
          }
          int new_monkey = monkey_test[monkey_i](new_item);
          monkey_items[monkey_i].pop_front();
          monkey_items[new_monkey].push_back(new_item);
        }
      }
    }
    std::sort(monkey_inspections.begin(), monkey_inspections.end(), std::greater<long long>());
    std::cout << "Part " << (part_i == 1 ? "One: " : "Two: ") << monkey_inspections[0] * monkey_inspections[1] << '\n';
  }
  
  return 0;
}
