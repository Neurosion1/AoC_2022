//
//  main.cpp
//  AoC_16
//
//  Created by Neurosion on 12/15/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Straightforward DFS approach. Part 2 just solves for player 1 and then solves for player 2
// with the remaining valves. This approach works on the actual input because the solution
// space is large enough to support it. It does not work on the practice data, which is a
// much smaller search space that can be fully explored well before either player runs out of
// time.

namespace
{
  struct Node
  {
    std::string name_;
    std::unordered_set<std::string> neighbors_;
    std::unordered_map<Node *, int> distances_;
    int flow_rate_;
  };

  struct State
  {
    long long open_valves_;
    int open_flow_;
    int total_flow_;
    Node * active_node_;
    int active_node_distance_;
  };

  int bfs(const std::unordered_map<std::string, Node *>& all_nodes, const Node * this_node, const Node * that_node)
  {
    std::unordered_map<const Node *, int> visit_map;
    for (auto node : all_nodes) {
      if (node.second != this_node) {
        visit_map[node.second] = INT_MIN;
      }
    }
    visit_map[this_node] = 0;
    std::queue<const Node *> next;
    next.push (this_node);
    
    while (!next.empty()) {
      const Node * curr = next.front();
      int step = visit_map[curr];
      for (auto neighbor : curr->neighbors_) {
        Node * this_neighbor = all_nodes.find(neighbor)->second;
        if (visit_map[this_neighbor] == INT_MIN) {
          if (neighbor == that_node->name_) {
            return step + 1;
          }
          else {
            next.push(this_neighbor);
            visit_map[this_neighbor] = step + 1;
          }
        }
      }
      next.pop();
    }
    
    return -1;
  }

  bool pick(const std::vector<Node *>& node_v, int i, State& state, int minutes_remaining)
  {
    Node * this_node = state.active_node_;
    if ((state.open_valves_ & (1ll << i)) == 0) {
      Node * that_node = node_v[i];
      int that_distance = this_node->distances_[that_node];
      if (that_distance + 1 <= minutes_remaining) {
        state.active_node_ = that_node;
        state.open_valves_ |= (1ll << i);
        state.active_node_distance_ = that_distance;
        return true;
      }
    }
    return false;
  }

  int best = INT_MIN;
  State best_state;

  void step(const std::vector<Node *>& node_v, State state, int minutes_remaining)
  {
    if (state.active_node_distance_ > 0) {
      minutes_remaining -= state.active_node_distance_;
      state.total_flow_ += (state.open_flow_ * state.active_node_distance_);
      state.open_flow_ += state.active_node_->flow_rate_;
      state.active_node_distance_ = 0;
      step(node_v, state, minutes_remaining);
    }
    else {
      --minutes_remaining;
      state.total_flow_ += state.open_flow_;
      for (int i = 0; i < node_v.size(); ++i) {
        State new_state = state;
        if (pick(node_v, i, new_state, minutes_remaining)) {
          step(node_v, new_state, minutes_remaining);
        }
      }
    }
    
    auto remaining = state.total_flow_ + (state.open_flow_ * minutes_remaining);
    if (remaining > best) {
      best = remaining;
      best_state = state;
    }
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_16_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  Node * start_room = nullptr;
  std::vector<Node *> node_v;
  std::unordered_map<std::string, Node *> all_nodes;
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    std::string name = line.substr(6, 2);
    size_t equal = line.find('='), semi = line.find(';');
    int flow_rate = atoi(line.substr(equal + 1, (equal + 1) - semi).c_str());
    std::unordered_set<std::string> neighbors;
    size_t comma = line.find(',');
    while (comma != std::string::npos) {
      neighbors.insert(line.substr(comma - 2, 2));
      comma = line.find(',', comma + 2);
    }
    neighbors.insert(line.substr(line.size() - 2, 2));
    Node * new_node = new Node;
    new_node->name_ = name;
    new_node->neighbors_ = neighbors;
    new_node->flow_rate_ = flow_rate;
    all_nodes.insert({ name, new_node });
    if (new_node->flow_rate_ > 0) {
      node_v.push_back(new_node);
    }
    if (name == "AA") {
      start_room = new_node;
    }
  }
  
  // Start room has no flow, but we add it just long enough to calculate
  // its distances to the rooms that do.
  node_v.push_back(start_room);
  for (int i = 0; i < node_v.size() - 1; ++i) {
    auto this_node = node_v[i];
    for (int j = i + 1; j < node_v.size(); ++j) {
      auto that_node = node_v[j];
      int distance = bfs(all_nodes, this_node, that_node);
      this_node->distances_.insert( { that_node, distance } );
      that_node->distances_.insert( { this_node, distance } );
    }
  }
  node_v.resize(node_v.size() - 1);
  
  State start_state = {};
  start_state.active_node_ = start_room;
  step(node_v, start_state, 30);
  std::cout << "Part One: " << best << '\n';
  best = INT_MIN;
  step(node_v, start_state, 26);
  start_state.open_valves_ = best_state.open_valves_;
  int player_1_best = best;
  best = INT_MIN;
  step(node_v, start_state, 26);
  std::cout << "Part Two: " << best + player_1_best << '\n';
  
  return 0;
}
