//
//  main.cpp
//  AoC_9
//
//  Created by Neurosion on 12/8/22.
//

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <array>

namespace
{
  enum class Dir { eNone = 0, eRight = 1, eLeft = 2, eDown = 4, eUp = 8,
                              eRD    = 5, eLD   = 6, eRU   = 9, eLU = 10 };
  Dir move_link(std::pair<int, int>& H, std::pair<int, int>& T, Dir dir)
  {
    int x_diff = (H.first  - T.first);
    int y_diff = (H.second - T.second);
    std::pair<int, int> T_start = T;
    
    if (abs(x_diff) > 1 || abs(y_diff) > 1) {
      if (x_diff != 0 && y_diff != 0) {
        if (dir == Dir::eRight || dir == Dir::eLeft) {
          T.second = H.second;
          y_diff = 0;
        }
        else if (dir == Dir::eUp || dir == Dir::eDown) {
          T.first = H.first;
          x_diff = 0;
        }
        else // Diagonal move
        {
          switch (dir)
          {
            case Dir::eRU:
              ++T.first;
              --T.second;
              break;
            case Dir::eLU:
              --T.first;
              --T.second;
              break;
            case Dir::eRD:
              ++T.first;
              ++T.second;
              break;
            case Dir::eLD:
              --T.first;
              ++T.second;
              break;
            default:
              assert(false);
          }
          return dir;
        }
      }
      if (x_diff == 0) {
        T.second = H.second + (dir == Dir::eDown ? -1 : 1 );
      }
      else if (y_diff == 0) {
        T.first = H.first + (dir == Dir::eRight ? -1 : 1);
      }
    }
    Dir retval = Dir::eNone;
    if (T.first < T_start.first) {
      retval = Dir::eLeft;
    }
    else if (T.first > T_start.first) {
      retval = Dir::eRight;
    }
    if (T.second < T_start.second) {
      retval = static_cast<Dir>(static_cast<int>(retval) | static_cast<int>(Dir::eUp));
    }
    else if (T.second > T_start.second) {
      retval = static_cast<Dir>(static_cast<int>(retval) | static_cast<int>(Dir::eDown));
    }
    return retval;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_9_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  // X Y
  std::set<std::pair<int, int>> visited;
  std::pair<int, int> H = { 0, 0 };
  std::pair<int, int> T = { 0, 0 };
  
  std::vector<std::pair<char, int>> items;
  while (!input.eof()) {
    char c;
    int n;
    input >> c >> n;
    std::pair<char, int> p = { c, n };
    items.push_back(p);
  }
  
  visited.insert( { 0, 0 });
  for (auto item : items) {
    Dir dir = Dir::eNone;
    switch (item.first)
    {
      case 'R': dir = Dir::eRight; break;
      case 'L': dir = Dir::eLeft;  break;
      case 'D': dir = Dir::eDown;  break;
      case 'U': dir = Dir::eUp;    break;
    }
    int cnt = item.second;
    for (int i = 0; i < cnt; ++i) {
      switch (dir)
      {
        case Dir::eRight: ++H.first; break;
        case Dir::eLeft:  --H.first; break;
        case Dir::eDown:  ++H.second; break;
        case Dir::eUp:    --H.second; break;
      }
      if (i != cnt) {
        move_link(H, T, dir);
      }
      visited.insert( { T.first, T.second });
    }
  }
  std::cout << "Part One: " << visited.size() << '\n';
  
  int min_x = INT_MAX, max_x = INT_MIN, min_y = INT_MAX, max_y = INT_MIN;
  visited.clear();
  visited.insert( { 0, 0 });
  std::array<std::pair<int, int>, 10> links;
  links.fill( { 0, 0 });
  for (auto item : items) {
    Dir dir = Dir::eNone;
    switch (item.first)
    {
      case 'R': dir = Dir::eRight; break;
      case 'L': dir = Dir::eLeft;  break;
      case 'D': dir = Dir::eDown;  break;
      case 'U': dir = Dir::eUp;    break;
    }
    int cnt = item.second;
    for (int i = 0; i < cnt; ++i) {
      switch (dir)
      {
        case Dir::eRight: ++links[0].first; break;
        case Dir::eLeft:  --links[0].first; break;
        case Dir::eDown:  ++links[0].second; break;
        case Dir::eUp:    --links[0].second; break;
        default: assert(false); break;
      }
      Dir curr_dir = dir;
      for (int j = 0; j < 9 && curr_dir != Dir::eNone; ++j) {
        curr_dir = move_link(links[j], links[j + 1], curr_dir);
      }
      min_x = std::min(min_x, links[9].first);
      min_y = std::min(min_y, links[9].second);
      max_x = std::max(max_x, links[9].first);
      max_y = std::max(max_y, links[9].second);
      visited.insert( { links[9].first, links[9].second });
      for (int y = -10; y < 10; ++y) {
        for (int x = -10; x < 10; ++x) {
          int found = -1;
          for (int i = 0; i < 10 && found < 0; ++i) {
            if (links[i].first == x && links[i].second == y) {
              found = i;
            }
          }
          std::cout << static_cast<char>(found == -1 ? ' ' : '1' + found);
        }
        std::cout << '\n';
      }
      std::cout << '\n';
    }
  }
#if 0
  for (int y = min_y; y < max_y + 1; ++y) {
    for (int x = min_x; x < max_x + 1; ++x) {
      if (visited.count( { x, y }) == 1) {
        std::cout << '#';
      }
      else {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
#endif
  std::cout << "Part Two: " << visited.size() << '\n';
  
  // 2574 too high
  
  return 0;
}
