//
//  main.cpp
//  AoC_17
//
//  Created by Neurosion on 12/17/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <array>
#include <set>

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
  bool try_move(const std::deque<std::string>& well, const Shape& shape, long long bottom, int y_offset, int x_offset, Move m)
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
  
  // The "state" contains the current gust/shape indices along with a
  // memoization of the stack of shapes to the point beyond which no
  // shape (most importantly the straight vertical line) can "drop."
  // When we find a state where the same gust sequence and the same
  // shape are going to approach the same pattern of blocks, we have
  // found a cycle.
  struct State
  {
    State(const std::deque<std::string>& well, long long bottom, int gust_index, int shape_index)
    {
      gust_index_ = gust_index;
      shape_index_ = shape_index;
      int blocked = 0;
      // The "bottom" row is always empty.
      for (long long row = bottom - 1; row > 0 && blocked < 127; --row) {
        int this_line = 0;
        for (int i = 0; i < 8; ++i) {
          if (well[row][i] == '#') {
            blocked |= (1 << i);
            this_line |= (1 << i);
          }
        }
        lines_.push_back(this_line);
      }
    }
    
    std::vector<int> lines_;
    int gust_index_;
    int shape_index_;
    
    bool operator<(const State& other) const
    {
      if (gust_index_ == other.gust_index_) {
        if (shape_index_ == other.shape_index_) {
          return lines_ < other.lines_;
        }
        else {
          return shape_index_ < other.shape_index_;
        }
      }
      else {
        return gust_index_ < other.gust_index_;
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
  
  // Flip all of the shapes to "fall up."
  for (auto & shape : shapes) {
    std::reverse(shape.begin(), shape.end());
  }
  
  std::string well_level = ".......";
  std::deque<std::string> well;
  std::deque<std::string> well_chunk(10, well_level);
  int shape_index = 0, gust_index = 0;
  long long count = 0, bottom = 0, skipped = 0;
  long long cycle_count_begin = 0, cycle_bottom_begin = 0, cycle_height = 0;
  std::set<State> states;
  std::set<State>::iterator cycle_state;
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
    
    if (++count == 2022ll) {
      std::cout << "Part One: " << bottom << '\n';
    }
    
    State state(well, bottom, gust_index, shape_index);
    if (count >= 2022ll) {
      if (cycle_count_begin == 0) {
        auto iter = states.find(state);
        if (iter == states.end()) {
          states.emplace(std::move(state));
        }
        else {
          cycle_count_begin = count;
          cycle_bottom_begin = bottom;
          cycle_state = iter;
        }
      }
      else if (state.shape_index_ == cycle_state->shape_index_ &&
               state.gust_index_  == cycle_state->gust_index_ &&
               state.lines_       == cycle_state->lines_) {
        cycle_height = bottom - cycle_bottom_begin;
        long long remaining = 1000000000000ll - count;
        long long cycle_length = count - cycle_count_begin;
        skipped = remaining / cycle_length;
        count += skipped * cycle_length;
      }
    }
  } while (count < 1000000000000ll);
  std::cout << "Part Two: " << bottom + (skipped * cycle_height) << '\n';
  return 0;
}
