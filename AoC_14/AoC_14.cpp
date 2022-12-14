//
//  main.cpp
//  AoC_14
//
//  Created by Neurosion on 12/14/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

namespace
{
  struct Point2D
  {
    int y_;
    int x_;
  };

  int simulate(std::vector<std::string> map, Point2D source)
  {
    bool done = false;
    int grains = 0;
    while (!done) {
      Point2D grain = source;
      bool rested = false;
      while (!rested && !done) {
        if (grain.y_ == map.size() - 1) {
          done = true;
        }
        else {
          if (map[grain.y_ + 1][grain.x_] == '.') {
            ++grain.y_;
          }
          else if (map[grain.y_ + 1][grain.x_ - 1] == '.') {
            ++grain.y_;
            --grain.x_;
          }
          else if (map[grain.y_ + 1][grain.x_ + 1] == '.') {
            ++grain.y_;
            ++grain.x_;
          }
          else {
            ++grains;
            rested = true;
            map[grain.y_][grain.x_] = 'o';
            if (grain.y_ == 0) {
              done = true;
            }
          }
        }
      }
    }
    return grains;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_14_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  int min_x = INT_MAX, max_x = INT_MIN, max_y = INT_MIN;
  std::vector<std::vector<Point2D>> raw_seams;
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    std::stringstream ss(line);
    std::vector<Point2D> this_seam;
    while (!ss.eof()) {
      Point2D this_point;
      std::string arrow;
      char c;
      ss >> this_point.x_ >> c >> this_point.y_ >> arrow;
      min_x = std::min(this_point.x_, min_x);
      max_x = std::max(this_point.x_, max_x);
      max_y = std::max(this_point.y_, max_y);
      this_seam.push_back(this_point);
    }
    raw_seams.push_back(this_seam);
  }
  
  std::string map_line((max_x - min_x) + 3, '.');
  std::vector<std::string> part_one_map(max_y + 1, map_line);
  for (auto & seam : raw_seams) {
    for (Point2D & point : seam) {
      point.x_ -= (min_x - 1);
    }
  }
  
  for (auto seam : raw_seams) {
    Point2D point = seam[0];
    for (int i = 1; i < seam.size(); ++i) {
      Point2D new_point = seam[i];
      if (point.x_ == new_point.x_) {
        if (point.y_ < new_point.y_) {
          for (int y = point.y_; y <= new_point.y_; ++y) {
            part_one_map[y][point.x_] = '#';
          }
        }
        else {
          for (int y = point.y_; y >= new_point.y_; --y) {
            part_one_map[y][point.x_] = '#';
          }
        }
      }
      else {
        if (point.x_ < new_point.x_) {
          for (int x = point.x_; x <= new_point.x_; ++x) {
            part_one_map[point.y_][x] = '#';
          }
        }
        else {
          for (int x = point.x_; x >= new_point.x_; --x) {
            part_one_map[point.y_][x] = '#';
          }
        }
      }
      point = new_point;
    }
  }
  Point2D part_one_source = { 0, (500 - min_x) + 1 };
  std::cout << "Part One: " << simulate(part_one_map, part_one_source) << '\n';
  
  int offset = 500;
  std::string part_two_line(offset * 2, '.');
  std::vector<std::string> part_two_map(max_y + 3, part_two_line);
  for (int y = 0; y < part_one_map.size(); ++y) {
    for (int x = 0; x < part_one_map[0].size(); ++x) {
      part_two_map[y][x + offset] = part_one_map[y][x];
    }
  }
  std::fill(part_two_map.rbegin()->begin(), part_two_map.rbegin()->end(), '#');
  Point2D part_two_source = { 0, part_one_source.x_ + offset };
  std::cout << "Part Two: " << simulate(part_two_map, part_two_source) << '\n';
  
  return 0;
}
