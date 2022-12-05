//
//  main.cpp
//  AoC_3
//
//  Created by Neurosion on 12/2/22.
//

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

namespace
{
  int score(char common)
  {
    if (common >= 'a' && common <= 'z') {
      return 1 + common - 'a';
    }
    else {
      return 27 + common - 'A';
    }
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_3_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  int elf_count = 0;
  long long total_1 = 0, total_2 = 0;
  std::set<char> badge_accum;
  while (!input.eof()) {
    ++elf_count;
    std::set<char> front, back, badge;
    std::string s;
    input >> s;
    auto fiter = s.begin();
    auto biter = s.rbegin();
    for (; fiter != biter.base(); ++fiter, ++biter) {
      front.insert(*fiter);
      back.insert(*biter);
      badge.insert(*fiter);
      badge.insert(*biter);
    }
    std::vector<char> intersection;
    std::set_intersection(front.begin(), front.end(),
                          back.begin(), back.end(),
                          std::back_inserter(intersection));
    assert(intersection.size() == 1);
    total_1 += score(intersection.front());
    if (elf_count == 1) {
      badge_accum = badge;
    }
    else {
      std::set<char> badge_intersection;
      std::set_intersection(badge_accum.begin(), badge_accum.end(),
                            badge.begin(), badge.end(),
                            std::inserter(badge_intersection, badge_intersection.begin()));
      if (elf_count == 3) {
        assert(badge_intersection.size() == 1);
        total_2 += score(*badge_intersection.begin());
        badge_accum.clear();
        elf_count = 0;
      }
      else {
        badge_accum = badge_intersection;
      }
    }
  }
  std::cout << "Part One: " << total_1 << '\n';
  std::cout << "Part Two: " << total_2 << '\n';
  
  return 0;
}
