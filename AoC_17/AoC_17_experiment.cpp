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

#if 0
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
#endif
  
  typedef std::vector<int> Shape;

  std::array<Shape, 5> original_shapes =
  {
    {
      {
        15
      },
      {
        1,
        3,
        1
      },
      {
        4,
        4,
        7
      },
      {
        1,
        1,
        1,
        1,
      },
      {
        3,
        3
      }
    }
  };
  
  std::array<Shape, 5> shapes =
  {
    {
      {
        15 << 2
      },
      {
        2 << 3,
        7 << 3,
        2 << 3
      },
      {
        4 << 1,
        4 << 1,
        7 << 3
      },
      {
        1 << 5,
        1 << 5,
        1 << 5,
        1 << 5,
      },
      {
        3 << 2,
        3 << 2
      }
    }
  };
  
  enum Move { eLeft, eRight, eDown };
  bool try_move(const std::string& well, const Shape& shape, int bottom, int y_offset, Move m, int shape_index)
  {
    if (m == eDown && y_offset + bottom == 0) {
      return false;
    }
    
    for (int y = 0; y < shape.size(); ++y) {
      auto original = original_shapes[shape_index];
      switch (m) {
        case Move::eDown:
          if ((well[y_offset + bottom + y - 1] & shape[y]) != 0) {
            return false;
          }
          break;
        case Move::eRight:
          if ((shape[y] >> 1) <= original_shapes[shape_index][y] || (well[y_offset + y + bottom] & (shape[y] >> 1)) != 0) {
            return false;
          }
          break;
        case Move::eLeft:
          if ((shape[y] << 1) > 255 || (well[y_offset + y + bottom] & (shape[y] << 1)) != 0) {
            return false;
          }
          break;
      }
    }
    return true;
  }
  
  void print_well(const std::string& well, const Shape& shape, int bottom, int y_offset)
  {
    std::vector<std::string> print;
    for (int i = 0; i <= bottom + 8; ++i) {
      std::string line(7, '.');
      for (int bit = 0; bit < 8; ++bit) {
        if (well[i] & (1 << bit)) {
          line[7 - bit] = '#';
        }
      }
      print.push_back(line);
    }
    
    for (int y = 0; y < shape.size(); ++y) {
      for (int bit = 0; bit < 8; ++bit) {
        if ((shape[y] & (1 << bit)) != 0) {
          print[bottom + y_offset + y][7 - bit] = '@';
        }
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
  
  int well_size = 10000000, well_trunc = well_size - 200;
  std::string well(well_size, 0);
  long long count = 0, cuts = 0;
  int shape_index = 0, gust_index = 0, bottom = 0;
  do {
    Shape shape = shapes[shape_index];
    shape_index %= 5;
    int y_offset = 3;
    if (well.size() < bottom + y_offset + shape.size()) {
      ++cuts;
      bottom -= well_trunc;
      well = well.substr(well_trunc);
      well.resize(well_size);
    }
    bool blocked = false;
    do {
      //print_well(well, shape, bottom, y_offset);
      Move move = (gusts[gust_index++] == '>' ? Move::eRight : Move::eLeft);
      gust_index %= gusts.size();
      if (try_move(well, shape, bottom, y_offset, move, shape_index)) {
        for (auto & s : shape) {
          if (move == Move::eRight) {
            s >>= 1;
          }
          else {
            s <<= 1;
          }
        }
      }
      if (try_move(well, shape, bottom, y_offset, Move::eDown, shape_index)) {
        --y_offset;
      }
      else {
        for (int y = 0; y < shape.size(); ++y) {
          well[y_offset + bottom + y] |= shape[y];
        }
        blocked = true;
      }
    } while (!blocked);
    if (bottom + y_offset + shape.size() > bottom) {
      bottom += y_offset + shape.size();
    }
    if (++count == 2022) {
      std::cout << "Part One: " << bottom + cuts * well_trunc << '\n';
    }
    shape_index = (shape_index + 1) % 5;
  } while (count < 1000000000000ll);
  
  return 0;
}
