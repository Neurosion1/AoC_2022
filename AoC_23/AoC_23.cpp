//
//  main.cpp
//  AoC_23
//
//  Created by Neurosion on 12/23/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>

namespace
{
  struct Point2D {
    int y_;
    int x_;
    bool operator<(const Point2D& other) const
    {
      if (y_ == other.y_) {
        return x_ < other.x_;
      }
      return y_ < other.y_;
    }
  };

  struct Elf {
    Point2D loc;
  };

  bool has_elf(const std::set<Point2D>& elf_locs, const Point2D& check_dir, const Point2D& offset)
  {
    return elf_locs.count( { check_dir.y_ + offset.y_, check_dir.x_ + offset.x_ }) > 0;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_23_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::vector<std::string> elf_map;
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    elf_map.push_back(line);
  }
  
  std::set<Point2D> elf_locs;
  std::vector<Elf> elves;
  for (int y = 0; y < elf_map.size(); ++y) {
    for (int x = 0; x < elf_map[y].size(); ++x) {
      if (elf_map[y][x] == '#') {
        Point2D loc = { y, x };
        elves.push_back( { loc } );
        elf_locs.insert(loc);
      }
    }
  }
  
  const std::array<Point2D, 8> all_dir =
  { { { -1, -1 }, { -1, 0 }, { -1,  1 },
      {  0, -1 },            {  0,  1 },
      {  1, -1 }, {  1, 0 }, {  1,  1 }
  }};
  std::array<Point2D, 4> move_dir = { { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } } };
  std::array<std::array<Point2D, 3>, 4> look_dir = { {
    { { { -1, -1 }, { -1,  0 }, { -1,  1 } } },
    { { {  1, -1 }, {  1,  0 }, {  1,  1 } } },
    { { { -1, -1 }, {  0, -1 }, {  1, -1 } } },
    { { { -1,  1 }, {  0,  1 }, {  1,  1 } } },
  }};
  
  int start_move_index = 0;
  
  int round = 0;
  bool moved = false;
  do {
    moved = false;
    ++round;
    std::multimap<Point2D, int> proposals;
    for (int elf_i = 0; elf_i < elves.size(); ++elf_i)
    {
      const Elf& elf = elves[elf_i];
      const Point2D& elf_loc = elf.loc;
      bool found = false;
      for (const auto & dir : all_dir) {
        if (has_elf(elf_locs, elf_loc, dir)) {
          found = true;
          break;
        }
      }
      if (found) {
        for (int dir_i = 0, check_dir = start_move_index; dir_i < 4; ++dir_i, check_dir = (dir_i + start_move_index) % 4)
        {
          const auto & this_move_dir = move_dir[check_dir];
          const auto & this_look_dir = look_dir[check_dir];
          if (!has_elf(elf_locs, elf_loc, this_look_dir[0]) &&
              !has_elf(elf_locs, elf_loc, this_look_dir[1]) &&
              !has_elf(elf_locs, elf_loc, this_look_dir[2]) ) {
            Point2D propose_point = { elf_loc.y_ + this_move_dir.y_, elf_loc.x_ + this_move_dir.x_ };
            proposals.insert({propose_point, elf_i});
            break;
          }
        }
      }
    }
    
    for (auto iter = proposals.begin(); iter != proposals.end();) {
      if (proposals.count(iter->first) == 1) {
        moved = true;
        elf_locs.erase(elf_locs.find(elves[iter->second].loc));
        elves[iter->second].loc = iter->first;
        elf_locs.insert(iter->first);
        ++iter;
      }
      else {
        iter = proposals.upper_bound(iter->first);
      }
    }
    
    start_move_index = (start_move_index + 1) % 4;
    
    if (round == 10) {
      int min_x = INT_MAX, max_x = INT_MIN, min_y = INT_MAX, max_y = INT_MIN;
      for (auto loc : elf_locs) {
        min_x = std::min(min_x, loc.x_);
        max_x = std::max(max_x, loc.x_);
        min_y = std::min(min_y, loc.y_);
        max_y = std::max(max_y, loc.y_);
      }
      
      std::cout << "Part One: " << ((max_x - min_x + 1) * (max_y - min_y + 1)) - elves.size() << '\n';
    }
  } while (moved);
  std::cout << "Part Two: " << round << '\n';
  
  return 0;
}
