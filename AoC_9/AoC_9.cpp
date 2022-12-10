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
#include <cassert>

namespace
{
  enum class Dir { eNone = 0, eRight = 1, eLeft = 2, eDown = 4, eUp = 8,
                              eRD    = 5, eLD   = 6, eRU   = 9, eLU = 10 };
  Dir move_link(std::pair<int, int>& H, std::pair<int, int>& T, Dir dir)
  {
    if (std::abs(T.first - H.first) > 2 || std::abs(T.second - H.second) > 2) {
      assert(false);
    }

    int x_diff = (H.first  - T.first);
    int y_diff = (H.second - T.second);
    std::pair<int, int> T_start = T;
    
    if (abs(x_diff) > 1 || abs(y_diff) > 1) {
      if (x_diff != 0 && y_diff != 0) {
        if (dir == Dir::eRight || dir == Dir::eLeft) {
          T.second += (y_diff > 0 ? 1 : -1);
          y_diff = 0;
        }
        else if (dir == Dir::eUp || dir == Dir::eDown) {
          T.first += (x_diff > 0 ? 1 : -1);
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
        T.second += (0 != (static_cast<int>(dir) & static_cast<int>(Dir::eDown))  ? 1 : -1);
      }
      else if (y_diff == 0) {
        T.first  += (0 != (static_cast<int>(dir) & static_cast<int>(Dir::eRight)) ? 1 : -1);
      }
    }

    if (std::abs(T.first - T_start.first) > 1 || std::abs(T.second - T_start.second) > 1) {
      assert(false);
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
  for (int index = 0; index < items.size(); ++index) {
    auto item = items[index];
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
  for (size_t index = 0; index < items.size(); ++index) {
    auto item = items[index];
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
      min_x = std::min(min_x, links[0].first);
      min_y = std::min(min_y, links[0].second);
      max_x = std::max(max_x, links[0].first);
      max_y = std::max(max_y, links[0].second);
      //print_chain(links, min_x, max_x, min_y, max_y);
      visited.insert( { links[9].first, links[9].second });
#if 0
      print_chain(links, min_x, max_x, min_y, max_y);
#endif
    }
  }
  std::cout << "Part Two: " << visited.size() << '\n';
  
  return 0;
}
