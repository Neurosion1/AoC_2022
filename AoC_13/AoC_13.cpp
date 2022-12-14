//
//  main.cpp
//  AoC_13
//
//  Created by Neurosion on 12/12/22.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

namespace
{
  struct List;
  struct Item
  {
    virtual bool is_list() const = 0;
    virtual std::shared_ptr<List> as_list() = 0;
  };

  struct List : public Item, public std::enable_shared_from_this<List>
  {
    std::vector<std::shared_ptr<Item>> list_;
    bool is_list() const override { return true; }
    std::shared_ptr<List> as_list() override
    {
      return shared_from_this();
    }
  };

  struct Value : public Item, public std::enable_shared_from_this<Value>
  {
    int value_;
    bool is_list() const override { return false; }
    std::shared_ptr<List> as_list() override
    {
      auto retval = std::make_shared<List>();
      retval->list_.push_back(shared_from_this());
      return retval;
    }
  };

  size_t find_right_brace(const std::string& s, size_t n)
  {
    int braces = 0;
    for (size_t i = n; i < s.size(); ++i) {
      if (s[i] == '[') {
        ++braces;
      }
      else if (s[i] == ']') {
        if (--braces == 0) {
          return i;
        }
      }
    }
    assert(false);
    return -1;
  }

  std::shared_ptr<List> parse(const std::string& input)
  {
    std::shared_ptr<List> retval = std::make_shared<List>();
    size_t i = 1;
    assert(input[0] == '[' && input[input.size() - 1] == ']');
    while (i < input.size() - 1) {
      if (input[i] == '[') {
        size_t right_brace = find_right_brace(input, i);
        retval->list_.emplace_back(parse(input.substr(i, (right_brace - i) + 1)));
        i = right_brace + 2; //Closing brace + comma
      }
      else {
        std::shared_ptr<Value> value = std::make_shared<Value>();
        size_t comma = input.find_first_of(",]", i);
        std::stringstream ss(input.substr(i, input.size() - comma + 1));
        ss >> value->value_;
        assert(!ss.fail());
        retval->list_.push_back(value);
        i = comma + 1;
      }
    }
    return retval;
  }

  enum Result { eUnknown, ePass, eFail };
  Result compare(std::shared_ptr<List> left, std::shared_ptr<List> right)
  {
    int i = 0;
    for (; i < left->list_.size(); ++i) {
      if (i >= right->list_.size()) {
        return eFail;
      }

      if (left->list_[i]->is_list() || right->list_[i]->is_list()) {
        Result result = compare(left->list_[i]->as_list(), right->list_[i]->as_list());
        if (result != eUnknown) {
          return result;
        }
      }
      else {
        int left_int = std::dynamic_pointer_cast<Value>(left->list_[i])->value_;
        int right_int = std::dynamic_pointer_cast<Value>(right->list_[i])->value_;
        if (left_int < right_int) {
          return ePass;
        }
        else if (left_int > right_int) {
          return eFail;
        }
      }
    }

    if (i == right->list_.size()) {
      return eUnknown;
    }

    return ePass;
  }

  bool compare_lt(std::shared_ptr<List> left, std::shared_ptr<List> right)
  {
    return compare(left, right) == ePass;
  }
}

int main(int argc, const char* argv[]) {
  std::ifstream input("AoC_13_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }

  std::vector<std::shared_ptr<List>> lists;
  int total = 0, current = 0;
  while (!input.eof()) {
    ++current;
    std::string left, right, blank;
    std::getline(input, left);
    std::getline(input, right);
    std::shared_ptr<List> left_list = parse(left);
    std::shared_ptr<List> right_list = parse(right);
    lists.push_back(left_list);
    lists.push_back(right_list);
    std::getline(input, blank);
    auto result = compare(left_list, right_list);
    if (result == ePass) {
      total += current;
    }
  }
  std::cout << "Part One: " << total << '\n';

  std::shared_ptr<List> start_index = parse("[[2]]");
  std::shared_ptr<List>   end_index = parse("[[6]]");
  lists.push_back(start_index);
  lists.push_back(end_index);
  std::sort(lists.begin(), lists.end(), compare_lt);

  int start_i = 0, end_i = 0;
  for (int i = 0; i < lists.size(); ++i) {
    if (lists[i] == start_index) { start_i = i + 1; }
    if (lists[i] == end_index) { end_i = i + 1; }
  }
  std::cout << "Part Two: " << start_i * end_i << '\n';

  return 0;
}
