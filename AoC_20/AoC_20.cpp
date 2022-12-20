//
//  main.cpp
//  AoC_20
//
//  Created by Neurosion on 12/20/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

namespace
{
  template<typename T>
  typename std::list<T>::const_iterator circularInc(std::list<T> &l, typename std::list<T>::const_iterator it)
  {
    return it == l.end() ? ++l.begin() : std::next(it);
  }

  template<typename T>
  typename std::list<T>::const_iterator circularDec(std::list<T> &l, typename std::list<T>::const_iterator it)
  {
    return it == l.begin() ? --l.end() : std::prev(it);
  }

  void run(const std::vector<long long>& originals, std::list<std::vector<long long>::const_iterator>& iterators)
  {
    long long length = originals.size();
    for (auto original_iter = originals.cbegin(); original_iter != originals.cend(); ++original_iter) {
      long long number = *original_iter;
      if (number == 0) {
        continue;
      }
      
      if (number < -(length - 1)) {
        number += (abs(number) / (length - 1) * (length - 1));
      }
      else if (number >= (length - 1)){
        number = (number % (length - 1));
      }
      
      for (auto iter = iterators.cbegin(); iter != iterators.cend(); ++iter) {
        if (*iter == original_iter) {
          auto start_iter = iter;
          iter = iterators.erase(iter);
          for (int i = 0; i < abs(number); ++i) {
            if (number < 0) {
              iter = circularDec(iterators, iter);
            }
            else {
              iter = circularInc(iterators, iter);
            }
          }
          iterators.insert(iter, *start_iter);
          break;
        }
      }
    }
  }

  long long score(const std::list<std::vector<long long>::const_iterator>& iterators)
  {
    long long retval = 0;
    auto iter = iterators.cbegin();
    while (**iter != 0) {
      ++iter;
    }
    
    for (int i = 1; i <= 3000; ++i) {
      if (++iter == iterators.end()) {
        iter = iterators.begin();
      }
      if (i % 1000 == 0) {
        retval += **iter;
      }
    }
    
    return retval;
  }
}

int main(int argc, const char * argv[]) {
  std::ifstream input("AoC_20_input.dat");
  if (input.fail()) {
    std::cout << "Didn't find the input file\n";
    return 1;
  }
  
  std::vector<long long> originals;
  while (!input.eof()) {
    long long this_number;
    input >> this_number;
    originals.push_back(this_number);
  }
  
  std::list<std::vector<long long>::const_iterator> iterators;
  for (auto iter = originals.cbegin(); iter != originals.cend(); ++iter) {
    iterators.push_back(iter);
  }
  
  run(originals, iterators);
  
  long long part_one_answer = score(iterators);
  std::cout << "Part One: " << part_one_answer << '\n';
  assert(part_one_answer == 7395 || part_one_answer == 3);
  
  iterators.clear();
  for (auto iter = originals.begin(); iter != originals.end(); ++iter) {
    *iter *= 811589153ll;
  }
  for (auto iter = originals.cbegin(); iter != originals.cend(); ++iter) {
    iterators.push_back(iter);
  }
  
  for (int i = 0; i < 10; ++i) {
    run(originals, iterators);
  }
  
  long long part_two_answer = score(iterators);
  std::cout << "Part Two: " << part_two_answer << '\n';
  assert(part_two_answer == 1640221678213 || part_two_answer == 1623178306);
  
  return 0;
}
