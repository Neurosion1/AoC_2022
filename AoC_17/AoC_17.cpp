//
//  main.cpp
//  AoC_17
//
//  Created by Neurosion on 12/17/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

namespace
{
  struct Point2D
  {
    int y_;
    int x_;
  };

// ####
//
// .#.
// ###
// .#.
//
// ..#
// ..#
// ###
//
// #
// #
// #
// #
//
// ##
// ##

  typedef std::vector<std::vector<Point2D>> Shape;

  std::array<Shape, 5> shapes =
  {
    {
      {
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } }
      },
      {
        {           { 0, 1 } },
        { { 1, 0 }, { 1, 1 }, { 1, 2 } },
        {           { 2, 1 } }
      },
      {
        {                     { 0, 2 } },
        {                     { 1, 2 } },
        { { 2, 0 }, { 2, 1 }, { 2, 2 } }
      },
      {
        { { 0, 0 } },
        { { 1, 0 } },
        { { 2, 0 } },
        { { 3, 0 } },
      },
      {
        { { 0, 0 }, { 0, 1 } },
        { { 1, 0 }, { 1, 1 } }
      }
    }
  };
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_17_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::vector<char> gusts;
  do {
    char c;
    input >> c;
    if (!input.eof()) {
      gusts.push_back(c);
    }
  }
  while (!input.eof());
  
  std::string well_level = "       ";
  std::deque<std::string> well;
  int index = 0, bottom = 0;
  bool done = false;
  do {
    const Shape & this_shape = shapes[index];
    int x_offset = 2;
    int y_offset = bottom + 3;
    if (well.size() < y_offset + this_shape.size()) {
      
    }
  } while (!done);
  
  
  return 0;
}
