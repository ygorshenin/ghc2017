#include "utils.h"

#include <algorithm>
#include <vector>
using namespace std;

int CalculateScore(const Problem &problem, const Solution &solution) {
  vector<vector<int>> caches(problem.m_numCaches);
  for (const auto &desc : solution.m_descriptions) {    
    caches[desc.m_cache] = desc.m_videos;
  }

  long long score = 0;
  long long totalRequests = 0;
  for (const auto &r : problem.m_requests) {
    const auto &e = problem.m_endpoints[r.m_endpoint];
    const int Ld = e.m_serverLatency;
    int L = Ld;
    for (const auto &link : e.m_links) {
      const auto &c = caches[link.m_cache];
      if (!binary_search(c.begin(), c.end(), r.m_video)) {
	continue;
      }
      L = min(L, link.m_latency);
    }
    score += static_cast<long long>(Ld - L) * static_cast<long long>(r.m_weight);
    totalRequests += r.m_weight;
  }

  score = score * 1000 / totalRequests;
  return score;
}
