//
//  main.cpp
//  AoC_15
//
//  Created by Neurosion on 12/14/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace
{
  struct Point2D
  {
    long long y_;
    long long x_;
  };

  enum class Part { one, two };
  long long solve_for_row(const std::vector<std::pair<Point2D, long long>>& sensor_info, int target_y, Part part)
  {
    std::vector<std::pair<long long, long long>> sensor_ranges;
    for (const auto & this_sensor_info : sensor_info) {
      const Point2D & sensor = this_sensor_info.first;
      long long sensor_range = this_sensor_info.second;
      long long y_dist = std::abs(sensor.y_ - target_y);
      if (y_dist < sensor_range) {
        long long x_dist = sensor_range - y_dist;
        sensor_ranges.push_back( { sensor.x_ - x_dist, sensor.x_ + x_dist } );
      }
    }
    std::sort(sensor_ranges.begin(), sensor_ranges.end());
    
    long long result = 0;
    auto iter = sensor_ranges.begin();
    std::pair<long long, long long> current_range = *iter++;
    for (;iter != sensor_ranges.end(); ++iter) {
      const std::pair<long long, long long>& this_range = *iter;
      if (this_range.first > current_range.second) {
        // There should be only one gap, and it should be one cell wide.
        assert(this_range.first  - current_range.second == 2);
        if (part == Part::two) {
          return current_range.second + 1;
        }
        else {
          assert(false);
        }
      }
      else if (current_range.second < this_range.second) {
        current_range.second = this_range.second;
      }
    }
    
    if (part == Part::two) {
      return -1;
    }
    return result + (current_range.second - current_range.first) + 1;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_15_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  // Stores sensor location and range to beacon
  std::vector<std::pair<Point2D, long long>> sensor_info;
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    std::string word;
    long long s_x, s_y, b_x, b_y;
    line = line.substr(line.find("x=") + 2);
    s_x = atoi(line.substr(0, line.find(",")).c_str());
    line = line.substr(line.find("y=") + 2);
    s_y = atoi(line.substr(0, line.find(",") + 2).c_str());
    line = line.substr(line.find("x=") + 2);
    b_x = atoi(line.substr(0, line.find(",") + 2).c_str());
    line = line.substr(line.find("y=") + 2);
    b_y = atoi(line.substr(0, line.find(",")).c_str());
    sensor_info.push_back( { { s_y, s_x }, std::abs(s_x - b_x) + std::abs(s_y - b_y) });
  }
  
  // A single beacon appears on this line (multiple times) in the test data.
  // Rather than spend time "finding" it we'll just account for it here.
  std::cout << "Part One: " << solve_for_row(sensor_info, 2000000, Part::one) - 1 << '\n';
  
  for (int y = 0; y <= 4000000; ++y) {
    long long x = solve_for_row(sensor_info, y, Part::two);
    if (x >= 0) {
      std::cout << "Part Two: " << (x * 4000000) + y << '\n';
      break;
    }
  }
  
  return 0;
}
