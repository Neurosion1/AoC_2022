//
//  main.cpp
//  AoC_6
//
//  Created by Neurosion on 12/5/22.
//

#include <iostream>
#include <fstream>
#include <string>

namespace
{
  int find_distinct_sequence_offset(const std::string& signal, int goal_length)
  {
    int distinct_sequence_length = 0, index = 0;
    int tracker[26] = {};
    while (index < signal.size()) {
      int char_in = signal[index] - 'a';
      if (++tracker[char_in] == 1) {
        ++distinct_sequence_length;
      }
      ++index;
      if (distinct_sequence_length == goal_length) {
        return index;
      }
      if (index >= goal_length) {
        int char_out = signal[index - goal_length] - 'a';
        if (--tracker[char_out] == 0) {
          --distinct_sequence_length;
        }
      }
    }
    return -1;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_6_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::string signal;
  input >> signal;
  
  std::cout << "Part One: " << find_distinct_sequence_offset(signal, 4) << '\n';
  std::cout << "Part Two: " << find_distinct_sequence_offset(signal, 14) << '\n';
  
  return 0;
}
