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

  typedef std::vector<std::vector<int>> Shape;

  std::array<Shape, 5> shapes =
  {
    {
      {
        { 0, 1, 2, 3 }
      },
      {
        {    1    },
        { 0, 1, 2 },
        {    1    }
      },
      {
        {       2 },
        {       2 },
        { 0, 1, 2 }
      },
      {
        { 0 },
        { 0 },
        { 0 },
        { 0 },
      },
      {
        { 0, 1 },
        { 0, 1 }
      }
    }
  };
  
  enum Move { eLeft, eRight, eDown };
  bool try_move(std::deque<std::string>& well, const Shape& shape, int bottom, int y_offset, int x_offset, Move m)
  {
    if (m == eDown && y_offset + bottom == 0) {
      return false;
    }
    for (int y = 0; y < shape.size(); ++y) {
      for (int x = 0; x < shape[y].size(); ++x) {
        switch (m) {
          case Move::eDown:
            if (well[y_offset + bottom + y - 1][x_offset + shape[y][x]] == '#') {
              return false;
            }
            break;
          case Move::eRight:
            if ((x_offset + shape[y][x]) == 6 || well[y_offset + y + bottom][x_offset + shape[y][x] + 1] == '#') {
              return false;
            }
            break;
          case Move::eLeft:
            if (x_offset == 0 || well[y_offset + y + bottom][x_offset + (shape[y][x] - 1)] == '#') {
              return false;
            }
            break;
        }
      }
    }
    return true;
  }
  
  void print_well(const std::deque<std::string>& well, const Shape& shape, int bottom, int y_offset, int x_offset)
  {
    auto print = well;
    for (int y = 0; y < shape.size(); ++y) {
      for (int x = 0; x < shape[y].size(); ++x) {
        print[bottom + y_offset + y][x_offset + shape[y][x]] = '@';
      }
    }
    for (auto line : print) {
      std::cout << line << '\n';
    }
    std::cout << '\n';
  }
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
  
  // Flip all of the shapes to "fall up."
  for (auto & shape : shapes) {
    std::reverse(shape.begin(), shape.end());
  }
  
  std::string well_level = ".......";
  std::deque<std::string> well;
  std::vector<std::string> well_chunk(10, well_level);
  int shape_index = 0, gust_index = 0, bottom = 0, count = 0;
  do {
    const Shape & shape = shapes[shape_index++];
    shape_index %= 5;
    int x_offset = 2;
    int y_offset = 3;
    if (well.size() < bottom + y_offset + shape.size()) {
      well.insert(well.end(), well_chunk.begin(), well_chunk.end());
    }
    bool blocked = false;
    do {
      Move move = (gusts[gust_index++] == '>' ? Move::eRight : Move::eLeft);
      gust_index %= gusts.size();
      if (try_move(well, shape, bottom, y_offset, x_offset, move)) {
        x_offset += (move == Move::eRight ? 1 : -1);
      }
      if (try_move(well, shape, bottom, y_offset, x_offset, Move::eDown)) {
        --y_offset;
      }
      else {
        for (int y = 0; y < shape.size(); ++y) {
          for (int x = 0; x < shape[y].size(); ++x) {
            well[y_offset + bottom + y][x_offset + shape[y][x]] = '#';
          }
        }
        blocked = true;
      }
    } while (!blocked);
    if (bottom + y_offset + shape.size() > bottom) {
      bottom += y_offset + shape.size();
    }
  } while (++count < 2022);
  std::cout << "Part One: " << bottom << '\n';
  
  return 0;
}
