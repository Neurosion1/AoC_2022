//
//  main.cpp
//  AoC_8
//
//  Created by Neurosion on 12/7/22.
//

#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_8_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  // The actual integer values don't matter, and '0' < '5' < '9', etc. so KISS
  std::vector<std::string> trees;
  while (!input.eof()) {
    std::string line;
    input >> line;
    trees.push_back(line);
  };
  
  std::vector<bool> vis_line(trees[0].size(), false);
  std::vector<std::vector<bool>> vis(trees.size(), vis_line);
  for (int y = 0; y < trees.size(); ++y) {
    int max = -1;
    for (size_t x = 0; x < trees[y].size(); ++x) {
      if (trees[y][x] > max) {
        max = trees[y][x];
        vis[y][x] = true;
      }
    }
    max = -1;
    for (int x = static_cast<int>(trees[y].size()) - 1; x >= 0; --x) {
      if (trees[y][x] > max) {
        max = trees[y][x];
        vis[y][x] = true;
      }
    }
  }
  
  for (int x = 0; x < trees[0].size(); ++x) {
    int max = -1;
    for (size_t y = 0; y < trees.size(); ++y) {
      if (trees[y][x] > max) {
        max = trees[y][x];
        vis[y][x] = true;
      }
    }
    max = -1;
    for (int y = static_cast<int>(trees.size() - 1); y >= 0; --y) {
      if (trees[y][x] > max) {
        max = trees[y][x];
        vis[y][x] = true;
      }
    }
  }
  
  int count = 0;
  for (auto vis_line : vis) {
    for (bool vis : vis_line) {
      if (vis) {
        ++count;
      }
    }
  }
  std::cout << "Part One: " << count << '\n';
  
  int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
  long long best_scenic = LLONG_MIN;
  for (int y = 1; y < trees.size() - 1; ++y) {
    for (int x = 1; x < trees[0].size() - 1; ++x) {
      long long scenic = 1;
      int max = trees[y][x];
      for (auto dir : dirs) {
        int count = 0;
        for (int my_x = x + dir[0], my_y = y + dir[1];
             my_x >= 0 && my_x < trees.size() && my_y >= 0 && my_y < trees.size();
             my_x += dir[0], my_y += dir[1]) {
          ++count;
          if (trees[my_y][my_x] >= max) {
            break;
          }
        }
        scenic *= count;
      }
      best_scenic = std::max(scenic, best_scenic);
    }
  }
  std::cout << "Part Two: " << best_scenic << '\n';
  
  return 0;
}
