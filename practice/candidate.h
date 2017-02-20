#pragma once

#include "problem.h"

#include <vector>

struct Candidate {
  Candidate() = default;

  Candidate(int row, int col, int height, int width)
      : row_(row), col_(col), height_(height), width_(width) {}

  int row_ = 0;
  int col_ = 0;
  int height_ = 0;
  int width_ = 0;
};

void FindCandidates(const Problem &problem, std::vector<Candidate> &candidates);
