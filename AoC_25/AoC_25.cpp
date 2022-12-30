//
//  main.cpp
//  AoC_25
//
//  Created by Neurosion on 12/25/22.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <deque>

namespace
{
  long long from_snafu(const std::string& in)
  {
    long long retval = 0;
    long long base = 1;
    for (auto iter = in.rbegin(); iter != in.rend(); ++iter) {
      switch (*iter) {
        case '-':
          retval -= base;
          break;
        case '=':
          retval -= base * 2;
          break;
        default:
          retval += base * (*iter - '0');
          break;
      }
      base *= 5;
    }
    return retval;
  }

  std::string to_snafu(long long work)
  {
    std::string retval;
    while (work > 0) {
      retval.push_back('0' + work % 5);
      work /= 5;
    }
    
    int carry = 0;
    for (auto iter = retval.begin(); iter != retval.end(); ++iter) {
      *iter += carry;
      if (*iter < '3') {
        carry = 0;
      }
      else {
        carry = 1;
        switch (*iter) {
          case '3':
            *iter = '=';
            break;
          case '4':
            *iter = '-';
            break;
          case '5':
            *iter = '0';
            break;
        }
      }
    }
    if (carry > 0) {
      retval.push_back('0' + carry);
    }
    
    return std::string(retval.rbegin(), retval.rend());
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_25_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  long long total = 0;
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    total += from_snafu(line);
  }
  std::cout << "Part One: " << to_snafu(total) << '\n';
  
  return 0;
}
