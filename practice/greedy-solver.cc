#include "candidate.h"
#include "fenwick.h"
#include "problem.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

namespace {
struct GreaterByArea {
  bool operator()(const Candidate &lhs, const Candidate &rhs) const {
    return lhs.Area() > rhs.Area();
  }
};
} // namespace

int main() {
  ios_base::sync_with_stdio(0);

  Problem problem;
  cin >> problem;

  vector<Candidate> candidates;
  FindCandidates(problem, candidates);

  cerr << "Num candidates: " << candidates.size() << endl;

  Fenwick2D fenwick(problem.num_rows_, problem.num_cols_);
  sort(candidates.begin(), candidates.end(), GreaterByArea());

  vector<Candidate> solution;

  for (const auto &candidate : candidates) {
    const int r1 = candidate.row_;
    const int c1 = candidate.col_;
    const int r2 = r1 + candidate.height_ - 1;
    const int c2 = c1 + candidate.width_ - 1;
    if (fenwick.Sum(r1, c1, r2, c2) == 0) {
      solution.push_back(candidate);
      for (int r = r1; r <= r2; ++r) {
        for (int c = c1; c <= c2; ++c)
          fenwick.Add(r, c, 1);
      }
    }
  }

  int num_cells = 0;
  cout << solution.size() << endl;
  for (const auto &candidate : solution) {
    cout << candidate << endl;
    num_cells += candidate.Area();
  }

  const int total_cells = problem.num_rows_ * problem.num_cols_;
  const double quality = static_cast<double>(num_cells) / total_cells;
  cerr << "Num cells: " << num_cells << endl;
  cerr << "Total cells: " << total_cells << endl;
  cerr << "Quality: " << quality << endl;
  return 0;
}
