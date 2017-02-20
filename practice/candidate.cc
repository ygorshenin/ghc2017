#include "candidate.h"

#include "fenwick.h"

#include <algorithm>
using namespace std;

void FindCandidates(const Problem &problem,
                    std::vector<Candidate> &candidates) {
  Fenwick2D fenwick(problem.num_rows_, problem.num_cols_);
  for (int i = 0; i < problem.num_rows_; ++i) {
    const auto &line = problem.pizza_[i];
    for (int j = 0; j < problem.num_cols_; ++j)
      fenwick.Add(i, j, line[j] == 'T');
  }

  for (int row = 0; row < problem.num_rows_; ++row) {
    for (int col = 0; col < problem.num_cols_; ++col) {
      const int max_width = problem.num_cols_ - col;
      for (int width = 1; width <= max_width; ++width) {
        const int min_height =
            (problem.min_num_ingridients_ * 2 + width - 1) / width;

        const int max_height =
            min(problem.num_rows_ - row, problem.max_num_cells_ / width);

        for (int height = min_height; height <= max_height; ++height) {
          const int num_tomatoes =
              fenwick.Sum(row, col, row + height - 1, col + width - 1);
          const int num_mushrooms = height * width - num_tomatoes;

          if (num_tomatoes >= problem.min_num_ingridients_ &&
              num_mushrooms >= problem.min_num_ingridients_) {
            candidates.emplace_back(row, col, height, width);
          }
        }
      }
    }
  }
}
