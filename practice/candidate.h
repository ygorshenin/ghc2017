#pragma once

#include "problem.h"

#include <iostream>
#include <vector>

struct Candidate {
  Candidate() = default;

  Candidate(int row, int col, int height, int width)
      : row_(row), col_(col), height_(height), width_(width) {}

  int Area() const { return height_ * width_; }

  int row_ = 0;
  int col_ = 0;
  int height_ = 0;
  int width_ = 0;
};

std::ostream &operator<<(std::ostream &os, const Candidate &candidate);

void FindCandidates(const Problem &problem, std::vector<Candidate> &candidates);
