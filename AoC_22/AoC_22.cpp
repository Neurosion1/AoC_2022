//
//  main.cpp
//  AoC_22
//
//  Created by Neurosion on 12/21/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <map>

// NOT A GENERAL PURPOSE SOLUTION. MATCHES THE FOLLOWING CUBE NET (50x50 per side):
//
//            0011
//            0011
//            22
//            22
//          3344
//          3344
//          55
//          55
//

namespace
{
  struct Point2D
  {
    int x_;
    int y_;
  };

  enum Facing { eFirst, eRight, eDown, eLeft, eUp, eLast } facing = eRight;

  struct Transformation
  {
    int new_side_;
    Facing new_facing_;
  };

  Point2D transform(Facing old_facing, Transformation transformation, Point2D old_loc)
  {
    if (old_facing == transformation.new_facing_) {
      // Continuing in the same direction; just jump from 49 on the old side to
      // 0 on the new side and vice versa
      if (old_facing == eLeft || old_facing == eRight) {
        return { 49 - old_loc.x_, old_loc.y_ };
      }
      else {
        return { old_loc.x_, 49 - old_loc.y_ };
      }
    }
    if (abs(static_cast<int>(old_facing) - static_cast<int>(transformation.new_facing_)) == 2) {
      // Flipping to the opposite direction; flip the appropriate edge, other coordinate remains the same
      if (old_facing == eLeft || old_facing == eRight) {
        return { old_loc.x_, 49 - old_loc.y_ };
      }
      else {
        return { 49 - old_loc.x_, old_loc.y_ };
      }
    }
    else {
      // All other transformations flip the x and y coordinates
      return { old_loc.y_, old_loc.x_ };
    }
  }

  struct Side
  {
    int y_offset_, x_offset_;
    std::array<std::string, 50> map_;
    std::map<Facing, Transformation> transformation_;
  };

  int walk(const std::array<Side, 6>& side, const std::vector<std::pair<char, int>>& moves)
  {
    Point2D loc = { 0, 0 };
    int current_side = 0;
    for (int move_i = 0; move_i < moves.size(); ++move_i) {
      auto move = moves[move_i];
      for (int i = 1; i <= move.second; ++i) {
        Point2D check = loc;
        switch (facing) {
          case eRight: check.x_ += 1; break;
          case eDown: check.y_ += 1; break;
          case eLeft: check.x_ -= 1; break;
          case eUp: check.y_ -= 1; break;
          default: assert(false);
        }
        if (check.x_ < 0 || check.x_ >= 50 || check.y_ < 0 || check.y_ >= 50) {
          auto transformation = side[current_side].transformation_.find(facing)->second;
          Point2D new_loc = transform(facing, transformation, loc);
          if (side[transformation.new_side_].map_[new_loc.y_][new_loc.x_] != '#') {
            loc = new_loc;
            current_side = transformation.new_side_;
            facing       = transformation.new_facing_;
          }
          else {
            break;
          }
        }
        else if (side[current_side].map_[check.y_][check.x_] != '#') {
          loc = check;
        }
        else {
          break;
        }
        assert(side[current_side].map_.at(loc.y_).at(loc.x_) == '.');
      }
      
      if (move.first == 'L') {
        facing = static_cast<Facing>(static_cast<int>(facing) - 1);
        if (facing == eFirst) {
          facing = eUp;
        }
      }
      else if (move.first == 'R') {
        facing = static_cast<Facing>(static_cast<int>(facing) + 1);
        if (facing == eLast) {
          facing = eRight;
        }
      }
    }
    
    return ((side[current_side].y_offset_ + loc.y_ + 1) * 1000) +
           ((side[current_side].x_offset_ + loc.x_ + 1) * 4) +
            (static_cast<int>(facing) - 1);
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_22_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  size_t max_width = 0;
  std::vector<std::string> raw_map;
  std::string line;
  std::getline(input, line);
  while (!line.empty()) {
    raw_map.push_back(line);
    std::getline(input, line);
    max_width = std::max(line.size(), max_width);
  }
  for (auto & line : raw_map) {
    if (line.size() < max_width) {
      line.resize(max_width, ' ');
    }
  }
  
  std::vector<std::pair<char, int>> moves;
  std::getline(input, line);
  size_t pos = 0;
  do {
    size_t new_pos = line.find_first_of("LR", pos);
    if (new_pos == std::string::npos) {
      moves.push_back( { 'F', atoi(line.substr(pos).c_str()) } );
    }
    else {
      moves.push_back( { line[new_pos], atoi(line.substr(pos, new_pos - pos).c_str()) } );
    }
    if (new_pos == std::string::npos) {
      break;
    }
    pos = new_pos + 1;
  } while (pos != std::string::npos);
  
  std::array<Side, 6> side =
  {
    {
                { 0,   50 }, { 0, 100 },
                { 50,  50 },
    { 100, 0 }, { 100, 50 },
    { 150, 0 }
      
    }
  };
  
  for (int i = 0; i < 6; ++i) {
    for (int y = 0; y < 50; ++y) {
      side[i].map_[y] = raw_map[y + side[i].y_offset_].substr(side[i].x_offset_, 50);
    }
  }
  
  // Flat. Going off one edge just zaps you to the opposite edge
  // continuing in the same direction.
  side[0].transformation_[eLeft]  = { 1, eLeft  };
  side[0].transformation_[eUp]    = { 4, eUp    };
  side[0].transformation_[eRight] = { 1, eRight };
  side[0].transformation_[eDown]  = { 2, eDown  };
  
  side[1].transformation_[eLeft]  = { 0, eLeft  };
  side[1].transformation_[eUp]    = { 1, eUp    };
  side[1].transformation_[eRight] = { 0, eRight };
  side[1].transformation_[eDown]  = { 1, eDown  };
  
  side[2].transformation_[eLeft]  = { 2, eLeft  };
  side[2].transformation_[eUp]    = { 0, eUp    };
  side[2].transformation_[eRight] = { 2, eRight };
  side[2].transformation_[eDown]  = { 4, eDown  };
  
  side[3].transformation_[eLeft]  = { 4, eLeft  };
  side[3].transformation_[eUp]    = { 5, eUp    };
  side[3].transformation_[eRight] = { 4, eRight };
  side[3].transformation_[eDown]  = { 5, eDown  };
  
  side[4].transformation_[eLeft]  = { 3, eLeft  };
  side[4].transformation_[eUp]    = { 2, eUp    };
  side[4].transformation_[eRight] = { 3, eRight };
  side[4].transformation_[eDown]  = { 0, eDown  };
  
  side[5].transformation_[eLeft]  = { 5, eLeft  };
  side[5].transformation_[eUp]    = { 3, eUp    };
  side[5].transformation_[eRight] = { 5, eRight };
  side[5].transformation_[eDown]  = { 3, eDown  };
  
  int part_one_result = walk(side, moves);
  std::cout << "Part One: " << part_one_result << '\n';
  assert(part_one_result == 146092);
  
  // Cube. Going off an edge walks you to the appropriate edge of the
  // appropriate side.
  side[0].transformation_[eLeft]  = { 3, eRight };
  side[0].transformation_[eUp]    = { 5, eRight };
  side[0].transformation_[eRight] = { 1, eRight };
  side[0].transformation_[eDown]  = { 2, eDown  };
  
  side[1].transformation_[eLeft]  = { 0, eLeft  };
  side[1].transformation_[eUp]    = { 5, eUp    };
  side[1].transformation_[eRight] = { 4, eLeft  };
  side[1].transformation_[eDown]  = { 2, eLeft  };
  
  side[2].transformation_[eLeft]  = { 3, eDown  };
  side[2].transformation_[eUp]    = { 0, eUp    };
  side[2].transformation_[eRight] = { 1, eUp    };
  side[2].transformation_[eDown]  = { 4, eDown  };
  
  side[3].transformation_[eLeft]  = { 0, eRight };
  side[3].transformation_[eUp]    = { 2, eRight };
  side[3].transformation_[eRight] = { 4, eRight };
  side[3].transformation_[eDown]  = { 5, eDown  };
  
  side[4].transformation_[eLeft]  = { 3, eLeft  };
  side[4].transformation_[eUp]    = { 2, eUp    };
  side[4].transformation_[eRight] = { 1, eLeft  };
  side[4].transformation_[eDown]  = { 5, eLeft  };
  
  side[5].transformation_[eLeft]  = { 0, eDown  };
  side[5].transformation_[eUp]    = { 3, eUp    };
  side[5].transformation_[eRight] = { 4, eUp    };
  side[5].transformation_[eDown]  = { 1, eDown  };
  
  int part_two_result = walk(side, moves);
  std::cout << "Part Two: " << part_two_result << '\n';
  assert(part_two_result == 110342);

  return 0;
}
