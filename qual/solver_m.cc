#include "utils.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;

random_device g_randomDevice;
mt19937 g_generator(g_randomDevice());

int main() {
  Problem problem;
  cin >> problem;

  const int numVids = problem.m_videos.size();
  const int numCaches = problem.m_numCaches;
  const int capacity = problem.m_capacity;
  auto &vidSz = problem.m_videos;

  vector<set<int>> videos(numCaches);
  vector<int> cap(numCaches, capacity);
  double startTime = clock();
  vector<tuple<int, int, int>> cand;
  long long bestSc = 0;
  while (clock() - startTime < 2.0 * CLOCKS_PER_SEC) {
    cand.clear();
    for (size_t i = 0; i < numCaches; ++i) {
      auto &v = videos[i];
      for (size_t j = 0; j < numVids; ++j) {
        if (v.count(j) > 0)
          continue;
        if (cap[i] - vidSz[j] >= 0) {
          cand.emplace_back(i, -1, j);
          continue;
	}
        for (int evicted : v) {
          if (cap[i] + vidSz[evicted] - vidSz[j] >= 0) {
            cand.emplace_back(i, evicted, j);
          }
        }
      }
    }

    for (const auto &cc : cand) {
      int i = get<0>(cc);
      int u = get<1>(cc);
      int v = get<2>(cc);
      if (u < 0 && v < 0) {
        continue;
      }
      if (u >= 0 && v >= 0 && cap[i] + vidSz[u] - vidSz[v] < 0) {
        continue;
      }
      if (v >= 0 && cap[i] - vidSz[v] < 0) {
        continue;
      }
      auto videosSav = videos;
      auto capSav = cap;

      videos[i].erase(u);
      if (u >= 0) {
        cap[i] += vidSz[u];
      }
      videos[i].insert(v);
      cap[i] -= vidSz[v];

      Solution sol(videos);
      const auto sc = CalculateScore(problem, sol);
      if (sc > bestSc) {
        bestSc = sc;
      } else {
        videos = videosSav;
        cap = capSav;
      }
    }
  }

  Solution solution(videos);
  cout << solution;
  cerr << "Score = " << CalculateScore(problem, solution) << endl;
  cerr << "Capacity = " << capacity << endl;
  return 0;
}
