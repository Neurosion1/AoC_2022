//
//  main.cpp
//  AoC_21
//
//  Created by Neurosion on 12/20/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

namespace
{
  struct Monkey;
  std::unordered_map<std::string, Monkey *> monkeys;
  struct Monkey {
    virtual long long get_number() const = 0;
    virtual long long solve(long long target) = 0;
  };

  struct Human : public Monkey
  {
    Human() : touched_(false) {}
    
    long long get_number() const override
    {
      touched_ = true;
      return -1;
    }
    
    long long solve(long long target) override
    {
      std::cout << "Part Two: " << target << '\n';
      return target;
    }
    
    bool touched() const { return touched_; }
    void reset() { touched_ = false; }
    
  private:
    mutable bool touched_;
  };
  Human * human = new Human;

  struct NumMonkey : public Monkey
  {
    NumMonkey(long long number) : number_(number) {}
    long long solve(long long target) override
    {
      assert(false);
      return -1;
    }
    long long get_number() const override { return number_; }
  private:
    long long number_;
  };

  struct OpMonkey : public Monkey
  {
    OpMonkey(const std::string& left, const std::string& right) : left_(left), right_(right) {}
    
  protected:
    std::string left_, right_;
  };

  struct AddMonkey : public OpMonkey
  {
    AddMonkey(const std::string& left, const std::string& right) : OpMonkey(left, right) {}
    
    long long get_number() const override
    {
      return monkeys[left_]->get_number() + monkeys[right_]->get_number();
    }
    
    long long solve(long long target) override
    {
      human->reset();
      auto left_monkey = monkeys[left_], right_monkey = monkeys[right_];
      long long left = left_monkey->get_number();
      if (human->touched()) {
        return left_monkey->solve(target - right_monkey->get_number());
      }
      else {
        return right_monkey->solve(target - left);
      }
    }
  };

  struct SubMonkey : public OpMonkey
  {
    SubMonkey(const std::string& left, const std::string& right) : OpMonkey(left, right) {}
    
    long long get_number() const override
    {
      return monkeys[left_]->get_number() - monkeys[right_]->get_number();
    }
    
    long long solve(long long target) override
    {
      human->reset();
      auto left_monkey = monkeys[left_], right_monkey = monkeys[right_];
      long long left = left_monkey->get_number();
      if (human->touched()) {
        return left_monkey->solve(target + right_monkey->get_number());
      }
      else {
        return right_monkey->solve(left - target);
      }
    }
  };

  struct MultMonkey : public OpMonkey
  {
    MultMonkey(const std::string& left, const std::string& right) : OpMonkey(left, right) {}
    
    long long get_number() const override
    {
      return monkeys[left_]->get_number() * monkeys[right_]->get_number();
    }
    
    long long solve(long long target) override
    {
      human->reset();
      auto left_monkey = monkeys[left_], right_monkey = monkeys[right_];
      long long left = left_monkey->get_number();
      if (human->touched()) {
        return left_monkey->solve(target / right_monkey->get_number());
      }
      else {
        return right_monkey->solve(target / left);
      }
    }
  };

  struct DivMonkey : public OpMonkey
  {
    DivMonkey(const std::string& left, const std::string& right) : OpMonkey(left, right) {}
    
    long long get_number() const override
    {
      return monkeys[left_]->get_number() / monkeys[right_]->get_number();
    }
    
    long long solve(long long target) override
    {
      human->reset();
      auto left_monkey = monkeys[left_], right_monkey = monkeys[right_];
      long long left = left_monkey->get_number();
      if (human->touched()) {
        return left_monkey->solve(target * right_monkey->get_number());
      }
      else {
        // Interestingly, test data never hits this.
        return right_monkey->solve(left / target);
      }
    }
  };
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_21_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  SubMonkey * part_two_root = nullptr;
  
  while (!input.eof()) {
    std::string line;
    std::getline(input, line);
    std::string name = line.substr(0, 4);
    if (line.find_first_of("+-/*") == std::string::npos) {
      monkeys.insert( { name, new NumMonkey(atoi(line.substr(6).c_str()))});
    }
    else {
      switch(line[11]) {
        case '+':
          monkeys.insert( { name, new AddMonkey(line.substr(6, 4), line.substr(13, 4))});
          break;
        case '-':
          monkeys.insert( { name, new SubMonkey(line.substr(6, 4), line.substr(13, 4))});
          break;
        case '*':
          monkeys.insert( { name, new MultMonkey(line.substr(6, 4), line.substr(13, 4))});
          break;
        case '/':
          monkeys.insert( { name, new DivMonkey(line.substr(6, 4), line.substr(13, 4))});
          break;
      }
      if (name == "root") {
        part_two_root = new SubMonkey(line.substr(6, 4), line.substr(13, 4));
      }
    }
  }
  std::cout << "Part One: " << monkeys["root"]->get_number() << '\n';
  
  monkeys["humn"] = human;
  part_two_root->solve(0);
    
  return 0;
}
