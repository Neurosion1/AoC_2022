//
//  main.cpp
//  AoC_2
//
//  Created by Neurosion on 12/1/22.
//
#include <iostream>
#include <fstream>
#include <cassert>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_2_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  char first, second;
  long long score_1 = 0, score_2 = 0;
  while (!input.eof()) {
    first = second = '*';
    input >> first >> second;
    switch (first)
    {
      case 'A':
        if (second == 'X') {
          score_1 += (1 + 3);
          score_2 += (0 + 3);
        }
        else if (second == 'Y') {
          score_1 += (2 + 6);
          score_2 += (3 + 1);
        }
        else if (second == 'Z') {
          score_1 += (3 + 0);
          score_2 += (6 + 2);
        }
        else {
          assert(false);
        }
        break;
      case 'B':
        if (second == 'X') {
          score_1 += (1 + 0);
          score_2 += (0 + 1);
        }
        else if (second == 'Y') {
          score_1 += (2 + 3);
          score_2 += (3 + 2);
        }
        else if (second == 'Z') {
          score_1 += (3 + 6);
          score_2 += (6 + 3);
        }
        else {
          assert(false);
        }
        break;
      case 'C':
        if (second == 'X') {
          score_1 += (1 + 6);
          score_2 += (0 + 2);
        }
        else if (second == 'Y') {
          score_1 += (2 + 0);
          score_2 += (3 + 3);
        }
        else if (second == 'Z') {
          score_1 += (3 + 3);
          score_2 += (6 + 1);
        }
        else {
          assert(false);
        }
        break;
    }
  }
  std::cout << "Part One: " << score_1 << '\n';
  std::cout << "Part Two: " << score_2 << '\n';
}
