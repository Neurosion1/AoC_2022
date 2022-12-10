//
//  main.cpp
//  AoC_10
//
//  Created by Neurosion on 12/9/22.
//

#include <iostream>
#include <fstream>
#include <array>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_10_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  int cycle = 1, X = 1, part_one_total = 0;
  std::array<std::basic_string<char>, 6> screen;
  screen.fill(std::basic_string<char>(40, ' '));
  while (!input.eof()) {
    std::string cmd;
    int addx_amount = 0;
    input >> cmd;
    int cmd_cycles = 1;
    if (cmd == "addx") {
      cmd_cycles = 2;
      input >> addx_amount;
    }
    for (int cmd_index = 0; cmd_index < cmd_cycles; ++cmd_index, ++cycle) {
      if ((cycle - 20) % 40 == 0) {
        // Interested in cycles 20, 60, 100, 140, 180, 220
        part_one_total += cycle * X;
      }
      // Print when cycle == X + { -1, 0, 1 }. Cycle is 1-indexed, so has to be
      // adjusted before modulo.
      if (abs((cycle - 1) % 40 - X) <= 1) {
        screen[cycle / 40][(cycle - 1) % 40] = '#';
      }
    }
    X += addx_amount;
  }
  std::cout << "Part One: " << part_one_total << "\n\n";
  
  for (auto line : screen) {
    std::cout << line <<'\n';
  }
  std::cout << '\n';
  
  return 0;
}
