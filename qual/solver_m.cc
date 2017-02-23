#include "utils.h"

#include <iostream>
#include <vector>
using namespace std;


int main() {
  Problem problem;
  cin >> problem;

  vector<vector<int>> videos(problem.m_numCaches);
  for (size_t i = 0; i < problem.m_numCaches; ++i) {
    int cap = problem.m_capacity;
    for (size_t j = 0; j < problem.m_videos.size(); ++j) {
      int v = problem.m_videos[j];
      if (cap >= v) {
	cap -= v;
	videos[i].push_back(j);
      }
    }
  }

  Solution solution(videos);
  cout << solution << endl;
  cerr << "Score = " << CalculateScore(problem, solution) << endl;
  return 0;
}
