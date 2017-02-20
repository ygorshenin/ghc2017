#include "candidate.h"

#include <algorithm>
using namespace std;

void FindCandidates(const Problem &problem,
                    std::vector<Candidate> &candidates) {
  vector<vector<int>> tomatoes_psums(problem.num_rows_,
                                     vector<int>(problem.num_cols_ + 1));
  for (int i = 0; i < problem.num_rows_; ++i) {
    const auto &line = problem.pizza_[i];
    for (int j = 1; j <= problem.num_cols_; ++j)
      tomatoes_psums[i][j] = tomatoes_psums[i][j - 1] + (line[j - 1] == 'T');
  }

  for (int row = 0; row < problem.num_rows_; ++row) {
    for (int col = 0; col < problem.num_cols_; ++col) {
      const int max_width = problem.num_cols_ - col;
      for (int width = 1; width <= max_width; ++width) {
        const int max_height =
            min(problem.num_rows_ - row, problem.max_num_cells_ / width);

        int num_tomatoes = 0;
        int num_mushrooms = 0;

        for (int height = 1; height <= max_height; ++height) {
          const auto &psums = tomatoes_psums[row + height - 1];
          const int cur_tomatoes = psums[col + width] - psums[col];
          num_tomatoes += cur_tomatoes;
          num_mushrooms += width - cur_tomatoes;

          if (num_tomatoes >= problem.min_num_ingridients_ &&
              num_mushrooms >= problem.min_num_ingridients_) {
            candidates.emplace_back(row, col, height, width);
          }
        }
      }
    }
  }
}
