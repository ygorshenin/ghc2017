#include "candidate.h"
#include "problem.h"

#include <iostream>
#include <vector>
using namespace std;

int main() {
  Problem problem;
  cin >> problem;

  vector<Candidate> candidates;
  FindCandidates(problem, candidates);

  clog << "Number of candidates: " << candidates.size() << endl;
  return 0;
}
