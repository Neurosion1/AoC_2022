//
//  main.cpp
//  AoC_24
//
//  Created by Neurosion on 12/24/22.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <numeric>
#include <array>
#include <utility>

namespace
{
  struct Point2D
  {
    int y_;
    int x_;
  };

  int run(std::vector<std::vector<std::vector<int>>> all_scores, std::vector<std::vector<std::string>> all_maps, Point2D start, Point2D end, int& current_map)
  {
    std::array<Point2D, 5> dir = { { { -1, 0 }, {1, 0}, {0, -1}, {0, 1}, { 0, 0} } } ;
    
    int max_step = INT_MIN;
    all_scores[current_map][start.y_][start.x_] = 0;
    std::queue<std::pair<int, Point2D>> next;
    next.push( std::make_pair(current_map, start));
    int score = 0;
    while (!next.empty()) {
      auto this_pair = next.front();
      current_map = this_pair.first;
      Point2D this_point = this_pair.second;
      next.pop();
      int step = all_scores[current_map][this_point.y_][this_point.x_];
      max_step = std::max(step, max_step);
      current_map = (current_map + 1) % all_maps.size();
      for (auto d : dir) {
        Point2D next_point = { this_point.y_ + d.y_, this_point.x_ + d.x_ };
        if (next_point.y_ > 0 || (next_point.y_ == 0 && next_point.x_ == 1)) {
          if (all_maps[current_map][next_point.y_][next_point.x_] == '.') {
            if (all_scores[current_map][next_point.y_][next_point.x_] == INT_MAX) {
              all_scores[current_map][next_point.y_][next_point.x_] = step + 1;
              if (next_point.y_ != end.y_) {
                next.push(std::make_pair(current_map, next_point));
              }
              else {
                score = step + 1;
                return score;
              }
            }
          }
        }
      }
    }
    return -1;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_24_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::vector<std::string> map;
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    map.push_back(line);
  }
  
  std::string empty_line(map[0].size(), '.');
  empty_line[0] = empty_line[map[0].size() - 1] = '#';
  std::vector<std::string> empty_map(map.size(), empty_line);
  std::fill(empty_map[0].begin(), empty_map[0].end(), '#');
  std::fill(empty_map[map.size() - 1].begin(), empty_map[map.size() - 1].end(), '#');
  empty_map[0][1] = '.';
  empty_map[map.size() - 1][map[0].size() - 2] = '.';
  std::vector<int> score_line(map[0].size(), INT_MAX);
  score_line[0] = INT_MIN;
  score_line[score_line.size() - 1] = INT_MIN;
  std::vector<std::vector<int>> score_map(map.size(), score_line);
  std::fill(score_map[0].begin(), score_map[0].end(), INT_MIN);
  std::fill(score_map[score_map.size() - 1].begin(), score_map[score_map.size() - 1].end(), INT_MIN);
  score_map[0][1] = INT_MAX;
  score_map[score_map.size() - 1][score_map[0].size() - 2] = INT_MAX;
  
  std::vector<std::vector<std::vector<int>>> all_scores;
  std::vector<std::vector<std::string>> all_maps;
  size_t active_x = map[0].size() - 2;
  size_t active_y = map.size() - 2;
  for (int tick = 0; tick < std::lcm(active_x, active_y); ++tick) {
    auto this_map = empty_map;
    for (int y = 1; y < map.size() - 1; ++y) {
      for (int x = 1; x < map[y].size() - 1; ++x) {
        switch (map[y][x]) {
          case '>':
          {
            int offset = ((x - 1) + tick) % active_x + 1;
            this_map[y][offset] = '*';
          }
            break;
          case '<':
          {
            int offset = x - (tick % active_x);
            if (offset < 1) {
              offset += active_x;
            }
            this_map[y][offset] = '*';
          }
            break;
          case 'v':
          {
            int offset = ((y - 1) + tick) % active_y + 1;
            this_map[offset][x] = '*';
          }
            break;
          case '^':
          {
            int offset = y - (tick % active_y);
            if (offset < 1) {
              offset += active_y;
            }
            this_map[offset][x] = '*';
          }
            break;
        }
      }
    }
    all_maps.push_back(this_map);
    all_scores.push_back(score_map);
  }
  int start_map = 0;
  Point2D start = { 0, 1 };
  Point2D   end = { static_cast<int>(map.size()) - 1, static_cast<int>(map[0].size()) - 2 };
  int steps = run(all_scores, all_maps, start, end, start_map);
  std::cout << "Part One: " << steps << '\n';
  steps += run(all_scores, all_maps, end, start, start_map);
  steps += run(all_scores, all_maps, start, end, start_map);
  std::cout << "Part Two: " << steps << '\n';
  
  return 0;
}
