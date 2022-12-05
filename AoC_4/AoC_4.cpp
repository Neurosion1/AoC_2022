//
//  main.cpp
//  AoC_4
//
//  Created by Neurosion on 12/3/22.
//

#include <iostream>
#include <fstream>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_4_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  int total_1 = 0, total_2 = 0;
  while (!input.eof()) {
    char c;
    int min_1, max_1, min_2, max_2;
    input >> min_1 >> c >> max_1 >> c >> min_2 >> c >> max_2;
    if ((min_1 <= min_2 && max_1 >= max_2) ||
        (min_2 <= min_1 && max_2 >= max_1)) {
      ++total_1;
    }
    if (min_1 <= max_2 && max_1 >= min_2) {
      ++total_2;
    }
  }
  std::cout << "Part One: " << total_1 << '\n';
  std::cout << "Part Two: " << total_2 << '\n';
  
  return 0;
}
