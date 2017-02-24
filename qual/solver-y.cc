#include "problem.h"
#include "solution.h"
#include "utils.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

Problem g_problem;

struct SortByLatency {
  bool operator()(Link const &lhs, Link const &rhs) const {
    return lhs.m_latency < rhs.m_latency;
  }
};

struct Cache {
  set<pair<double, int>> m_priorities;
  map<int, double> m_weights;
  map<int, vector<int>> m_requests;
  int m_used = 0;
};

Cache g_caches[1000];

int main() {
  cin >> g_problem;

  queue<int> requests;
  for (int i = 0; i < g_problem.m_requests.size(); ++i)
    requests.push(i);

  int processed = 0;
  while (!requests.empty()) {
    ++processed;
    if (processed >= 5 * g_problem.m_requests.size())
      break;

    const int r = requests.front();
    requests.pop();

    auto const &request = g_problem.m_requests[r];
    const int video = request.m_video;
    const int size = g_problem.m_videos[video];

    auto const &endpoint = g_problem.m_endpoints[request.m_endpoint];

    int bestLink = -1;
    double bestGain = 0;
    for (int i = 0; i < endpoint.m_links.size(); ++i) {
      int c = endpoint.m_links[i].m_cache;
      auto &cache = g_caches[c];

      double currGain = static_cast<double>(endpoint.m_serverLatency -
                                            endpoint.m_links[i].m_latency) *
                        request.m_weight / size;
      if (cache.m_weights.count(video) == 0 &&
          cache.m_used + size > g_problem.m_capacity) {
        double evictedGain = 0;

        int available = g_problem.m_capacity - cache.m_used;
        auto it = cache.m_priorities.begin();
        while (available < size && it != cache.m_priorities.end()) {
          evictedGain += it->first;
          available += g_problem.m_videos[it->second];
          ++it;
        }

        currGain -= evictedGain;
      }

      if (currGain > bestGain) {
        bestGain = currGain;
        bestLink = i;
      }
    }

    if (bestLink == -1)
      continue;

    int c = endpoint.m_links[bestLink].m_cache;
    auto &cache = g_caches[c];

    if (cache.m_weights.count(video) != 0) {
      cache.m_priorities.erase(make_pair(cache.m_weights[video], video));
      cache.m_weights[video] += bestGain;
      cache.m_priorities.insert(make_pair(cache.m_weights[video], video));
      cache.m_requests[video].emplace_back(r);
    } else {
      int available = g_problem.m_capacity - cache.m_used;
      auto it = cache.m_priorities.begin();
      while (available < size && it != cache.m_priorities.end()) {
        const int video = it->second;
        available += g_problem.m_videos[video];
        cache.m_used -= g_problem.m_videos[video];
        cache.m_weights.erase(video);
        for (auto r : cache.m_requests[video])
          requests.push(r);
        cache.m_requests.erase(video);
        ++it;
      }
      cache.m_priorities.erase(cache.m_priorities.begin(), it);

      cache.m_used += size;
      cache.m_weights[video] = bestGain;
      cache.m_priorities.insert(make_pair(cache.m_weights[video], video));
      cache.m_requests[video].emplace_back(r);
    }
  }

  Solution solution;
  solution.m_descriptions.resize(g_problem.m_numCaches);
  for (int i = 0; i < g_problem.m_numCaches; ++i) {
    auto &d = solution.m_descriptions[i];
    d.m_cache = i;
    for (auto p : g_caches[i].m_weights)
      d.m_videos.push_back(p.first);
  }

  clog << "Score: " << CalculateScore(g_problem, solution) << endl;
  cout << solution;
  return 0;
}
