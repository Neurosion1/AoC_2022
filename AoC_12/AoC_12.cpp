//
//  main.cpp
//  AoC_12
//
//  Created by Neurosion on 12/11/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>

namespace
{
  struct Point2D
  {
    int y_;
    int x_;
  };

  int bfs(const std::vector<std::string>& map, const Point2D& start, const Point2D& target)
  {
    std::vector<int> visit_line(map[0].size(), INT_MIN);
    std::vector<std::vector<int>> visit_map(map.size(), visit_line);
    visit_map[start.y_][start.x_] = 0;
    std::queue<Point2D> next;
    next.push (start);
    
    bool done = false;
    while (!done && !next.empty()) {
      Point2D curr = next.front();
      int step = visit_map[curr.y_][curr.x_];
      static std::array<std::pair<int, int>, 4> DIR = { { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } } };
      for (auto dir : DIR) {
        Point2D test = { curr.y_ + dir.first, curr.x_ + dir.second };
        if (test.x_ >= 0 && test.x_ < map[0].size() && test.y_ >= 0 && test.y_ < map.size()) {
          if (map[test.y_][test.x_] <= map[curr.y_][curr.x_] + 1 && visit_map[test.y_][test.x_] == INT_MIN) {
            if (test.y_ == target.y_ && test.x_ == target.x_) {
              return step + 1;
            }
            else {
              next.push(test);
              visit_map[test.y_][test.x_] = step + 1;
            }
          }
        }
      }
      next.pop();
      ++step;
    }
    
    return -1;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_12_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::vector<std::string> map;
  while (!input.eof()) {
    std::string map_line;
    input >> map_line;
    map.push_back(map_line);
  }
  
  std::vector<Point2D> part_two_starts;
  Point2D start, target;;
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[0].size(); ++x) {
      if (map[y][x] == 'S') {
        start = { y, x };
      }
      else if (map[y][x] == 'E') {
        target = { y, x };
      }
      else if (map[y][x] == 'a') {
        part_two_starts.push_back( { y, x } );
      }
    }
  }
  map[start.y_][start.x_] = 'a';
  map[target.y_][target.x_] = 'z';
  int best_result = bfs(map, start, target);
  std::cout << "Part One: " << best_result << '\n';
  
  for (auto start : part_two_starts) {
    int result = bfs(map, start, target);
    if (result >= 0) {
      best_result = std::min(best_result, result);
    }
  }
  std::cout << "Part Two: " << best_result << '\n';
  
  return 0;
}
