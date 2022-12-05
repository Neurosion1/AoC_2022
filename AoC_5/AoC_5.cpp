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
  
  std::deque<std::deque<char>> stacks_1(9);
  char buf[500];
  input.getline(buf, 500);
  while (strlen(buf) > 0) {
    int index = 1;
    while (index < strlen(buf)) {
      if (!(buf[index] >= '1' && buf[index] <= '9')) {
        char c = buf[index];
        if (c != ' ') {
          stacks_1[index / 4].push_back(c);
        }
      }
      index += 4;
    }
    input.getline(buf, 500);
  }
  auto stacks_2 = stacks_1;
  
  while (!input.eof()) {
    std::string word;
    int count, start, end;
    input >> word >> count >> word >> start >> word >> end;
    for (int i = 0; i < count; ++i) {
      stacks_1[end - 1].push_front(stacks_1[start - 1].front());
      stacks_1[start - 1].pop_front();
    }
    stacks_2[end - 1].insert(stacks_2[end - 1].begin(),
                             stacks_2[start - 1].begin(),
                             stacks_2[start - 1].begin() + count);
    stacks_2[start - 1].erase(stacks_2[start - 1].begin(),
                              stacks_2[start - 1].begin() + count);
  }
  
  std::string p1, p2;
  for (int i = 0; i < 9; ++i) {
    p1 += stacks_1[i].front();
    p2 += stacks_2[i].front();
  }
  std::cout << "Part One: " << p1 << '\n';
  std::cout << "Part Two: " << p2 << '\n';
  
  return 0;
}
