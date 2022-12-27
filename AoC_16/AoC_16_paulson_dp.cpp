//
//  main.cpp
//  AoC_16
//
//  Created by Neurosion on 12/15/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Dynamic programming-based solution as described by Jonathan Paulson at https://www.youtube.com/watch?v=DgqkVDr1WX8.
// It takes SIGNIFICANTLY longer than my DFS-based solution, but will not only work for both the practice data and any
// actual data, but could also be modified to work for any N players.

namespace
{
  struct Node
  {
    std::string name_;
    std::vector<std::string> neighbors_;
    std::vector<int> neighbors_i_;
    int valve_i;
    int flow_rate_;
  };

  std::vector<long long> scores;
  std::unordered_map<std::string, int> lookup = { { "AA", 0 } };

  long long step(const std::vector<Node *> nodes, int current_node_index, long long valves, int minutes, bool two_players)
  {
    if (minutes == 0) {
      if (two_players) {
        return step(nodes, 0, valves, 26, false);
      }
      else {
        return 0;
      }
    }
    
    long long check = valves * nodes.size() * 31 * 2 + current_node_index * 31 * 2 + minutes * 2 + two_players;
    if (scores[check] > LLONG_MIN) {
      long long score = scores[check];
      return score;
    }
    
    long long result = 0;
    Node * current_node = nodes[current_node_index];
    if (current_node->valve_i >= 0 && (valves & (1ll << current_node->valve_i)) == 0) {
      long long new_valves = valves | (1ll << current_node->valve_i);
      result = std::max(result, (minutes - 1) * current_node->flow_rate_ + step(nodes, current_node_index, new_valves, minutes - 1, two_players));
    }
    
    for (auto neighbor : current_node->neighbors_i_) {
      result = std::max(result, step(nodes, neighbor, valves, minutes - 1, two_players));
    }
    
    scores[check] = result;
    
    return result;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_16_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  int valve_index = 0;
  Node * start_room = nullptr;
  std::vector<Node *> node_v;
  node_v.push_back(nullptr); // Reserve the start room
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    
    Node * new_node = new Node;
    std::string name = line.substr(6, 2);
    new_node->name_ = name;
    size_t equal = line.find('='), semi = line.find(';');
    int flow_rate = atoi(line.substr(equal + 1, (equal + 1) - semi).c_str());
    new_node->flow_rate_ = flow_rate;
    if (new_node->flow_rate_ > 0) {
      new_node->valve_i = valve_index++;
    }
    else {
      new_node->valve_i = -1;
    }
    if (name == "AA") {
      node_v[0] = new_node;
      start_room = new_node;
    }
    else {
      node_v.push_back(new_node);
      lookup[name] = static_cast<int>(node_v.size()) - 1;
    }
    size_t comma = line.find(',');
    while (comma != std::string::npos) {
      new_node->neighbors_.push_back(line.substr(comma - 2, 2));
      comma = line.find(',', comma + 2);
    }
    new_node->neighbors_.push_back(line.substr(line.size() - 2, 2));
  }
  
  for (auto node : node_v) {
    for (auto neighbor : node->neighbors_) {
      node->neighbors_i_.push_back(lookup[neighbor]);
    }
  }
  
  scores.resize((1 << valve_index) * node_v.size() * 31 * 2, LLONG_MIN);
  
  std::cout << "Part One: " << step(node_v, 0, 0, 30, false) << '\n';
  std::cout << "Part Two: " << step(node_v, 0, 0, 26, true) << '\n';
  
  return 0;
}
