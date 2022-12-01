//
//  main.cpp
//  AoC_1
//
//  Created by Russ Bryan on 11/27/22.
//

#include <iostream>
#include <fstream>
#include <numeric>
#include <set>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_1_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::set<long long> all_sums;
  int sum = 0;
  while (!input.eof()) {
    char buf[100] = { 0 };
    input.getline(buf, 100);
    if (strlen(buf) > 0) {
      sum += atoi(buf);
    }
    if (strlen(buf) == 0 || input.eof()) {
      all_sums.insert(sum);
      sum = 0;
    }
  }
  
  auto iter = all_sums.rbegin();
  long long total = *iter++;
  std::cout << "Part One: " << total << '\n';
  
  total += *iter++;
  total += *iter;
  std::cout << "Part Two: " << total << '\n';
  
  return 0;
}
