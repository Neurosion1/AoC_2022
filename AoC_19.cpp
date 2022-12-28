// AoC_19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <map>

namespace
{
  std::vector<std::string> p1_test = {
    "Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.",
    "Blueprint 2: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 8 clay. Each geode robot costs 3 ore and 12 obsidian." };
    
  std::vector<std::string> p2_test = {
    "Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian." };

  std::vector<std::string> p1_input = {
    "Blueprint 1: Each ore robot costs 3 ore. Each clay robot costs 4 ore.Each obsidian robot costs 3 ore and 10 clay.Each geode robot costs 2 ore and 7 obsidian.",
    "Blueprint 2: Each ore robot costs 4 ore. Each clay robot costs 4 ore.Each obsidian robot costs 4 ore and 12 clay.Each geode robot costs 3 ore and 8 obsidian.",
    "Blueprint 3: Each ore robot costs 4 ore. Each clay robot costs 4 ore.Each obsidian robot costs 4 ore and 17 clay.Each geode robot costs 2 ore and 13 obsidian.",
    "Blueprint 4: Each ore robot costs 2 ore. Each clay robot costs 2 ore.Each obsidian robot costs 2 ore and 20 clay.Each geode robot costs 2 ore and 14 obsidian.",
    "Blueprint 5: Each ore robot costs 3 ore. Each clay robot costs 4 ore.Each obsidian robot costs 4 ore and 5 clay.Each geode robot costs 3 ore and 12 obsidian.",
    "Blueprint 6: Each ore robot costs 2 ore. Each clay robot costs 4 ore. Each obsidian robot costs 4 ore and 11 clay. Each geode robot costs 3 ore and 8 obsidian.",
    "Blueprint 7: Each ore robot costs 3 ore. Each clay robot costs 4 ore. Each obsidian robot costs 3 ore and 17 clay. Each geode robot costs 3 ore and 7 obsidian.",
    "Blueprint 8: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 11 clay. Each geode robot costs 2 ore and 16 obsidian.",
    "Blueprint 9: Each ore robot costs 3 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 9 clay. Each geode robot costs 3 ore and 7 obsidian.",
    "Blueprint 10: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 4 ore and 9 clay. Each geode robot costs 4 ore and 16 obsidian.",
    "Blueprint 11: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 2 ore and 16 clay. Each geode robot costs 4 ore and 16 obsidian.",
    "Blueprint 12: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 2 ore and 17 clay. Each geode robot costs 3 ore and 19 obsidian.",
    "Blueprint 13: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 2 ore and 10 clay. Each geode robot costs 3 ore and 14 obsidian.",
    "Blueprint 14: Each ore robot costs 4 ore. Each clay robot costs 3 ore. Each obsidian robot costs 2 ore and 13 clay. Each geode robot costs 2 ore and 10 obsidian.",
    "Blueprint 15: Each ore robot costs 3 ore. Each clay robot costs 3 ore. Each obsidian robot costs 2 ore and 19 clay. Each geode robot costs 2 ore and 12 obsidian.",
    "Blueprint 16: Each ore robot costs 4 ore. Each clay robot costs 3 ore. Each obsidian robot costs 2 ore and 20 clay. Each geode robot costs 3 ore and 9 obsidian.",
    "Blueprint 17: Each ore robot costs 3 ore. Each clay robot costs 4 ore. Each obsidian robot costs 2 ore and 11 clay. Each geode robot costs 2 ore and 10 obsidian.",
    "Blueprint 18: Each ore robot costs 2 ore. Each clay robot costs 4 ore. Each obsidian robot costs 4 ore and 18 clay. Each geode robot costs 2 ore and 11 obsidian.",
    "Blueprint 19: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 3 ore and 8 obsidian.",
    "Blueprint 20: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 4 ore and 8 clay. Each geode robot costs 4 ore and 14 obsidian.",
    "Blueprint 21: Each ore robot costs 2 ore. Each clay robot costs 4 ore. Each obsidian robot costs 3 ore and 20 clay. Each geode robot costs 2 ore and 17 obsidian.",
    "Blueprint 22: Each ore robot costs 3 ore. Each clay robot costs 4 ore. Each obsidian robot costs 3 ore and 15 clay. Each geode robot costs 4 ore and 16 obsidian.",
    "Blueprint 23: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 2 ore and 17 clay. Each geode robot costs 3 ore and 11 obsidian.",
    "Blueprint 24: Each ore robot costs 3 ore. Each clay robot costs 3 ore. Each obsidian robot costs 2 ore and 13 clay. Each geode robot costs 3 ore and 12 obsidian.",
    "Blueprint 25: Each ore robot costs 3 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 19 clay. Each geode robot costs 3 ore and 17 obsidian.",
    "Blueprint 26: Each ore robot costs 3 ore. Each clay robot costs 4 ore. Each obsidian robot costs 3 ore and 12 clay. Each geode robot costs 3 ore and 17 obsidian.",
    "Blueprint 27: Each ore robot costs 3 ore. Each clay robot costs 4 ore. Each obsidian robot costs 2 ore and 15 clay. Each geode robot costs 3 ore and 7 obsidian.",
    "Blueprint 28: Each ore robot costs 3 ore. Each clay robot costs 4 ore. Each obsidian robot costs 4 ore and 14 clay. Each geode robot costs 4 ore and 10 obsidian.",
    "Blueprint 29: Each ore robot costs 3 ore. Each clay robot costs 3 ore. Each obsidian robot costs 2 ore and 15 clay. Each geode robot costs 3 ore and 9 obsidian.",
    "Blueprint 30: Each ore robot costs 4 ore. Each clay robot costs 4 ore. Each obsidian robot costs 2 ore and 7 clay. Each geode robot costs 4 ore and 13 obsidian." };
  
  std::vector<std::string> p2_input = {
    "Blueprint 1: Each ore robot costs 3 ore. Each clay robot costs 4 ore.Each obsidian robot costs 3 ore and 10 clay.Each geode robot costs 2 ore and 7 obsidian.",
    "Blueprint 2: Each ore robot costs 4 ore. Each clay robot costs 4 ore.Each obsidian robot costs 4 ore and 12 clay.Each geode robot costs 3 ore and 8 obsidian.",
    "Blueprint 3: Each ore robot costs 4 ore. Each clay robot costs 4 ore.Each obsidian robot costs 4 ore and 17 clay.Each geode robot costs 2 ore and 13 obsidian."};



  struct Factory
  {
    bool part_one_;
    int ore_robot_ore_;
    int clay_robot_ore_;
    int obs_robot_ore_;
    int obs_robot_clay_;
    int geode_robot_ore_;
    int geode_robot_obs_;
    int max_ore() const
    {
      static int max = std::max(ore_robot_ore_, std::max(clay_robot_ore_, std::max(obs_robot_ore_, geode_robot_ore_)));
      return max;
    }
  };

  struct State
  {
    State() :
      current_ore_(0),
      current_clay_(0),
      current_obs_(0),
      current_geode_(0),
      ore_robots_(1),
      clay_robots_(0),
      obs_robots_(0),
      geode_robots_(0),
      minute_(0)
    {
      
    }
    
    bool operator<(const State& other) const {
      if (minute_ != other.minute_) {
        return minute_ < other.minute_;
      }
      if (current_ore_ != other.current_ore_) {
        return current_ore_ < other.current_ore_;
      }
      if (current_clay_ != other.current_clay_) {
        return current_clay_ < other.current_clay_;
      }
      if (current_obs_ != other.current_obs_) {
        return current_obs_ < other.current_obs_;
      }
      if (current_geode_ != other.current_geode_) {
        return current_geode_ < other.current_geode_;
      }
      if (ore_robots_ != other.ore_robots_) {
        return ore_robots_ < other.ore_robots_;
      }
      if (clay_robots_ != other.clay_robots_) {
        return clay_robots_ < other.clay_robots_;
      }
      if (obs_robots_ != other.obs_robots_) {
        return obs_robots_ < other.obs_robots_;
      }
      return geode_robots_ < other.geode_robots_;
    }
    
    int minute_, current_ore_, current_clay_, current_obs_, current_geode_, max_ore_;
    int ore_robots_, clay_robots_, obs_robots_, geode_robots_;
  };
  
  std::map<State, int> best;

  int best_geode_ = 0;

  int step(const Factory& factory, State state)
  {
    int total_minutes = (factory.part_one_ ? 24 : 32);
    
    bool build_ore_robot = state.current_ore_ >= factory.ore_robot_ore_;
    bool build_clay_robot = state.current_ore_ >= factory.clay_robot_ore_;
    bool build_obs_robot = state.current_ore_ >= factory.obs_robot_ore_ && state.current_clay_ >= factory.obs_robot_clay_;
    bool build_geode_robot = state.current_ore_ >= factory.geode_robot_ore_ && state.current_obs_ >= factory.geode_robot_obs_;
    
    state.current_ore_ += state.ore_robots_;
    state.current_clay_ += state.clay_robots_;
    state.current_obs_ += state.obs_robots_;
    state.current_geode_ += state.geode_robots_;
    
    ++state.minute_;
    auto iter = best.find(state);
    if (iter != best.end()) {
      return iter->second;
    }
    
    if (state.minute_ == total_minutes) {
      best_geode_ = std::max(best_geode_, state.current_geode_);
      return state.current_geode_;
    }
    
    int best_move = 0;
    if (build_geode_robot) {
      State next_state = state;
      next_state.current_ore_ -= factory.geode_robot_ore_;
      next_state.current_obs_ -= factory.geode_robot_obs_;
      ++next_state.geode_robots_;
      best_move = std::max(best_move, step(factory, next_state));
    }
    else {
      if (build_obs_robot) {
        if (state.obs_robots_ < factory.geode_robot_obs_) {
          State next_state = state;
          next_state.current_ore_ -= factory.obs_robot_ore_;
          next_state.current_clay_ -= factory.obs_robot_clay_;
          ++next_state.obs_robots_;
          best_move = std::max(best_move, step(factory, next_state));
        }
      }
      
      if (build_clay_robot) {
        if (state.clay_robots_ < factory.obs_robot_clay_) {
          State next_state = state;
          next_state.current_ore_ -= factory.clay_robot_ore_;
          ++next_state.clay_robots_;
          best_move = std::max(best_move, step(factory, next_state));
        }
      }
      
      if (build_ore_robot) {
        if (state.ore_robots_ < factory.max_ore()) {
          State next_state = state;
          next_state.current_ore_ -= factory.ore_robot_ore_;
          ++next_state.ore_robots_;
          best_move = std::max(best_move, step(factory, next_state));
        }
      }
      
      if (!build_geode_robot && !build_obs_robot) {
        State last_state = state;
        best_move = std::max(best_move, step(factory, last_state));
      }
    }
    
    if (best.find(state) != best.end()) {
      assert(false);
    }
    best.insert( { state, best_move });
    return best_move;
  }
}

int main()
{
  for (int part = 1; part <= 2; ++part) {
    long long total = (part == 1 ? 0 : 1);
    std::vector<std::string> blueprints = (part == 1 ? p1_input : p2_input);
    std::vector<Factory> factories;
    for (long long b = 1; b < blueprints.size() + 1; ++b) {
      std::string s = blueprints[b - 1];
      Factory this_factory;
      size_t loc = 20;
      std::array<int *, 4> ore_costs = { &this_factory.ore_robot_ore_, &this_factory.clay_robot_ore_, &this_factory.obs_robot_ore_, &this_factory.geode_robot_ore_ };
      for (int i = 0; i < 4; ++i) {
        size_t ore_pos = s.find(" ore", loc);
        auto test = s.substr(ore_pos - 1, 1);
        *ore_costs[i] = atoi(s.substr(ore_pos - 1, 1).c_str());
        loc = ore_pos + 3;
        if (i == 2) {
          size_t clay_pos = s.find(" clay.");
          size_t num_begin = s.rfind(' ', clay_pos - 1);
          this_factory.obs_robot_clay_ = atoi(s.substr(num_begin, clay_pos - num_begin).c_str());
          loc = clay_pos;
        }
        else if (i == 3) {
          size_t obs_pos = s.find(" obsidian.");
          size_t num_begin = s.rfind(' ', obs_pos - 1);
          this_factory.geode_robot_obs_ = atoi(s.substr(num_begin, obs_pos - num_begin).c_str());
        }
      }
      this_factory.part_one_ = (part == 1);
      State state;
      step(this_factory, state);
      if (part == 1) {
        total += (best_geode_ * b);
      }
      else {
        total *= best_geode_;
      }
      best.clear();
      best_geode_ = 0;
    }
    if (part == 1) {
      std::cout << "Part One: " << total << '\n';
    }
    else {
      std::cout << "Part Two: " << total << '\n';
    }
  }
}
