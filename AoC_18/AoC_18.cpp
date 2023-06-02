//
//  main.cpp
//  AoC_18
//
//  Created by Neurosion on 12/18/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <array>
#include <queue>
#include <tuple>

namespace
{
  struct Point3D
  {
    long long x_;
    long long y_;
    long long z_;
    int exposed_faces_;
    bool operator<(const Point3D& other) const
    {
      if (x_ == other.x_) {
        if (y_ == other.y_) {
          return z_ < other.z_;
        }
        else {
          return y_ < other.y_;
        }
      }
      else {
        return x_ < other.x_;
      }
    }
    bool operator==(const Point3D& other) const
    {
      return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
    }
  };
  
  void bfs(std::vector<std::vector<std::vector<bool>>> search_space, Point3D& cube)
  {
    int exposed_faces = cube.exposed_faces_ = 0;
    std::list<Point3D> remaining;
    if (cube.x_ == 0) {
      ++exposed_faces;
    }
    else {
      remaining.push_back({ cube.x_ - 1, cube.y_, cube.z_ });
    }
    
    if (cube.x_ == search_space[0][0].size() - 1) {
      ++exposed_faces;
    }
    else {
      remaining.push_back({ cube.x_ + 1, cube.y_, cube.z_ });
    }
    
    if (cube.y_ == 0) {
      ++exposed_faces;
    }
    else {
      remaining.push_back({ cube.x_, cube.y_ - 1, cube.z_ });
    }
    
    if (cube.y_ == search_space[0].size() - 1) {
      ++exposed_faces;
    }
    else {
      remaining.push_back({ cube.x_, cube.y_ + 1, cube.z_ });
    }
    
    if (cube.z_ == 0) {
      ++exposed_faces;
    }
    else {
      remaining.push_back({ cube.x_, cube.y_, cube.z_  - 1});
    }
    
    if (cube.z_ == search_space.size() - 1) {
      ++exposed_faces;
    }
    else {
      remaining.push_back({ cube.x_, cube.y_, cube.z_ + 1 });
    }
    
    for (auto remaining_iter = remaining.begin(); remaining_iter != remaining.end();) {
      Point3D remaining_cube = *remaining_iter++;
      if (!search_space[remaining_cube.z_][remaining_cube.y_][remaining_cube.x_]) {
        int face_count = 1;
        static std::array<std::tuple<int, int, int>, 6> DIR =
        {
          {
            { 1, 0, 0 }, { -1,  0,  0 },
            { 0, 1, 0 }, {  0, -1,  0 },
            { 0, 0, 1 }, {  0,  0, -1 }
          }
        };
        bool exposed = false;
        std::queue<Point3D> next;
        next.push(remaining_cube);
        while (!next.empty()) {
          Point3D this_cube = next.front();
          next.pop();
          for (int i = 0; i < DIR.size(); ++i) {
            auto dir = DIR[i];
            Point3D search_cube = {
              this_cube.x_ + std::get<0>(dir),
              this_cube.y_ + std::get<1>(dir),
              this_cube.z_ + std::get<2>(dir) };
            if (search_cube.z_ < 0 || search_cube.z_ > search_space.size() - 1 ||
                search_cube.y_ < 0 || search_cube.y_ > search_space[0].size() - 1 |
                search_cube.x_ < 0 || search_cube.x_ > search_space[0][0].size() - 1) {
              exposed = true;
            }
            else {
              if (!search_space[search_cube.z_][search_cube.y_][search_cube.x_]) {
                auto check_iter = std::find(remaining_iter, remaining.end(), search_cube);
                if (check_iter != remaining.end()) {
                  ++face_count;
                }
                search_space[search_cube.z_][search_cube.y_][search_cube.x_] = true;
                next.push(search_cube);
              }
            }
          }
        }
        if (exposed) {
          exposed_faces += face_count;
        }
      }
    }
    cube.exposed_faces_ = exposed_faces;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_18_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  long long min_x = LLONG_MAX, max_x = LLONG_MIN,
            min_y = LLONG_MAX, max_y = LLONG_MIN,
            min_z = LLONG_MAX, max_z = LLONG_MIN;
  std::vector<Point3D> cube;
  while (!input.eof()) {
    Point3D this_cube;
    char c;
    input >> this_cube.x_ >> c >> this_cube.y_ >> c >> this_cube.z_;
    cube.push_back(this_cube);
    min_x = std::min(min_x, this_cube.x_);
    max_x = std::max(max_x, this_cube.x_);
    min_y = std::min(min_y, this_cube.y_);
    max_y = std::max(max_y, this_cube.y_);
    min_z = std::min(min_z, this_cube.z_);
    max_z = std::max(max_z, this_cube.z_);
  }
  
  for (auto & this_cube : cube) {
    this_cube.z_ -= min_z;
    this_cube.y_ -= min_y;
    this_cube.x_ -= min_x;
  }
  
  long long part_one_total = 0;
  for (auto this_cube : cube) {
    int faces = 6;
    Point3D check_cube = {this_cube.x_ - 1, this_cube.y_, this_cube.z_};
    if (std::find(cube.begin(), cube.end(), check_cube) != cube.end()) {
      --faces;
    }
    check_cube.x_ = this_cube.x_ + 1;
    if (std::find(cube.begin(), cube.end(), check_cube) != cube.end()) {
      --faces;
    }
    check_cube.x_ = this_cube.x_;
    check_cube.y_ = this_cube.y_ - 1;
    if (std::find(cube.begin(), cube.end(), check_cube) != cube.end()) {
      --faces;
    }
    check_cube.y_ = this_cube.y_ + 1;
    if (std::find(cube.begin(), cube.end(), check_cube) != cube.end()) {
      --faces;
    }
    check_cube.y_ = this_cube.y_;
    check_cube.z_ = this_cube.z_ - 1;
    if (std::find(cube.begin(), cube.end(), check_cube) != cube.end()) {
      --faces;
    }
    check_cube.z_ = this_cube.z_ + 1;
    if (std::find(cube.begin(), cube.end(), check_cube) != cube.end()) {
      --faces;
    }
    this_cube.exposed_faces_ = faces;
    part_one_total += faces;
  }
  std::cout << "Part One: " << part_one_total << '\n';
  
  std::vector<bool> line((max_x - min_x) + 1, false);
  std::vector<std::vector<bool>> sheet((max_y - min_y) + 1, line);
  std::vector<std::vector<std::vector<bool>>> space((max_z - min_z) + 1, sheet);
  for (auto & this_cube : cube) {
    space[this_cube.z_][this_cube.y_][this_cube.x_] = true;
    this_cube.exposed_faces_ = 0;
  }
  
  int part_two_total = 0;
  for (auto & this_cube : cube) {
    bfs(space, this_cube);
    part_two_total += this_cube.exposed_faces_;
  }
  std::cout << "Part Two: " << part_two_total << '\n';
  
  return 0;
}
