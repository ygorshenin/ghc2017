#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Problem {
  std::istream &Read(std::istream &is);

  std::vector<std::string> pizza_;
  int num_rows_ = 0;
  int num_cols_ = 0;
  int min_num_ingridients_ = 0;
  int max_num_cells_ = 0;
};

inline std::istream &operator>>(std::istream &is, Problem &problem) {
  return problem.Read(is);
}
