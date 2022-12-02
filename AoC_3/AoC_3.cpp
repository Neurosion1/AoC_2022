//
//  main.cpp
//  AoC_3
//
//  Created by Neurosion on 12/2/22.
//

#include <iostream>
#include <fstream>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_3_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  return 0;
}
