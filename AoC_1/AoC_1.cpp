//
//  main.cpp
//  AoC_1
//
//  Created by Russ Bryan on 11/27/22.
//

#include <iostream>
#include <fstream>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_1_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  return 0;
}
