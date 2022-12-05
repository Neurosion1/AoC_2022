//
//  main.cpp
//  AoC_5
//
//  Created by Neurosion on 12/4/22.
//

#include <iostream>
#include <fstream>
#include <deque>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_5_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  char buf[500];
  input.getline(buf, 500);
  std::deque<std::deque<char>> stacks_1(strlen(buf) / 4 + 1);
  while (strlen(buf) > 0) {
    size_t index = 1, len = strlen(buf);
    while (index < len) {
      char c = buf[index];
      if (c >= 'A' && c <= 'Z') {
        stacks_1[index / 4].push_back(c);
      }
      index += 4;
    }
    input.getline(buf, 500);
  }
  auto stacks_2 = stacks_1;
  
  while (!input.eof()) {
    std::string word;
    int count, start_n, target_n;
    input >> word >> count >> word >> start_n >> word >> target_n;
    auto & start_1 = stacks_1[start_n - 1], & target_1 = stacks_1[target_n - 1];
    target_1.insert(target_1.begin(), std::reverse_iterator(start_1.begin() + count), start_1.rend());
    start_1.erase(start_1.begin(), start_1.begin() + count);
    auto & start_2 = stacks_2[start_n - 1], & target_2 = stacks_2[target_n - 1];
    target_2.insert(target_2.begin(), start_2.begin(), start_2.begin() + count);
    start_2.erase(start_2.begin(), start_2.begin() + count);
  }
  
  std::string p1, p2;
  for (int i = 0; i < stacks_1.size(); ++i) {
    p1 += stacks_1[i].front();
    p2 += stacks_2[i].front();
  }
  std::cout << "Part One: " << p1 << '\n';
  std::cout << "Part Two: " << p2 << '\n';
  
  return 0;
}
