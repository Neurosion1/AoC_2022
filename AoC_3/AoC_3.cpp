//
//  main.cpp
//  AoC_3
//
//  Created by Neurosion on 12/2/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

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
  std::string badge;
  while (!input.eof()) {
    std::string s;
    input >> s;
    std::string front = s.substr(0, s.size() / 2), back = s.substr(s.size() / 2);
    for (char c : front) {
      size_t pos = back.find_first_of(c);
      if (pos != std::string::npos) {
        total_1 += score(c);
        break;
      }
    }
    std::sort(s.begin(), s.end());
    if (++elf_count % 3 == 1) {
      badge.swap(s);
    }
    else {
      std::string intersection;
      std::set_intersection(badge.begin(), badge.end(),
                            s.begin(), s.end(),
                            std::back_inserter(intersection));
      if (elf_count % 3 == 0) {
        total_2 += score(*intersection.begin());
        badge.clear();
      }
      else {
        badge.swap(intersection);
      }
    }
  }
  std::cout << "Part One: " << total_1 << '\n';
  std::cout << "Part Two: " << total_2 << '\n';
  
  return 0;
}
