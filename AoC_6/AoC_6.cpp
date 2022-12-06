//
//  main.cpp
//  AoC_6
//
//  Created by Neurosion on 12/5/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

namespace
{
  int find_distinct_sequence_offset(const std::string& signal, int goal_length)
  {
    int distinct_sequence_length = 0, index = 0;
    std::unordered_map<char, int> tracker;
    while (index < signal.size()) {
      tracker[signal[index]]++;
      if (tracker[signal[index]] == 1) {
        ++distinct_sequence_length;
      }
      else if (tracker[signal[index]] == 2) {
        --distinct_sequence_length;
      }
      ++index;
      if (distinct_sequence_length == goal_length) {
        return index;
      }
      if (index >= goal_length) {
        tracker[signal[index - goal_length]]--;
        if (tracker[signal[index - goal_length]] == 1) {
          ++distinct_sequence_length;
        }
        else if (tracker[signal[index - goal_length]] == 0) {
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
