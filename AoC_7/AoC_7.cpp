//
//  main.cpp
//  AoC_7
//
//  Created by Neurosion on 12/6/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>

namespace
{
  struct Directory
  {
    Directory(const std::string& name, std::shared_ptr<Directory> parent) :
      size_(0), name_(name), total_size_(LLONG_MIN), parent_(parent) {}
    void add_directory(std::shared_ptr<Directory> d) { contents_.insert({d->name_, d}); }
    void add_file(long long size) { size_ += size; }
    long long total_size() const
    {
      // If this were "real" we'd have to reset this (recursively) on any add.
      if (total_size_ == LLONG_MIN) {
        total_size_ = 0;
        for (auto dir : contents_) {
          total_size_ += dir.second->total_size();
        }
        total_size_ += size_;
      }
      return total_size_;
    }
    long long size_;
    std::string name_;
    mutable long long total_size_;
    std::shared_ptr<Directory> parent_;
    std::unordered_map<std::string, std::shared_ptr<Directory>> contents_;
  };
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_7_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::shared_ptr<Directory> cwd;
  std::vector<std::shared_ptr<Directory>> directories;
  auto root = std::make_shared<Directory>("/", nullptr);
  std::string line;
  std::getline(input, line);
  while (!input.eof()) {
    assert (line[0] == '$');
    if (line.substr(2, 2) == "cd") {
      std::string filename = line.substr(5);
      if (filename == "..") {
        cwd = cwd->parent_;
      }
      else if (filename == "/"){
        cwd = root;
      }
      else {
        cwd = cwd->contents_[filename];
      }
      std::getline(input, line);
    }
    else {
      do {
        std::getline(input, line);
        if (line[0] != '$' && !input.eof()) {
          size_t space = line.find_first_of(' ');
          if (line.substr(0, space) == "dir") {
            auto new_dir = std::make_shared<Directory>(line.substr(space + 1), cwd);
            cwd->add_directory(new_dir);
            directories.push_back(new_dir);
          }
          else {
            cwd->add_file(atoi(line.substr(0, space).c_str()));
          }
        }
      } while (line[0] != '$' && !input.eof());
    }
  }
  
  long long total = 0;
  for (auto iter = directories.begin(); iter != directories.end(); ++iter) {
    if ((*iter)->total_size() <= 100000) {
      total += (*iter)->total_size();
    }
  }
  std::cout << "Part One: " << total << '\n';
  
  long long free_space = 70000000 - root->total_size();
  long long need_space = 30000000 - free_space;
  long long smallest_dir_size = LLONG_MAX;
  for (auto dir : directories) {
    long long size = dir->total_size();
    if (size >= need_space && size < smallest_dir_size) {
      smallest_dir_size = size;
    }
  }
  std::cout << "Part Two: " << smallest_dir_size << '\n';
  
  return 0;
}
