#include "problem.h"
#include "solution.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

const int kMaxCaches = 1000;
const int kMaxEndpoints = 1000;

struct Cache {
  std::unordered_set<int> m_videos;
  int m_used = 0;
};

Problem g_problem;
Cache g_caches[kMaxCaches];

int g_linkedCaches[kMaxEndpoints];
vector<int> g_linkedEndpoints[kMaxCaches];

int GetBestLink(Request const &request) {
  auto const &endpoint = g_problem.m_endpoints[request.m_endpoint];

  int video = request.m_video;
  int videoSize = g_problem.m_videos[video];

  int bestSavings = 0;
  int bestLink = -1;

  for (int i = 0; i < endpoint.m_links.size(); ++i) {
    auto const &link = endpoint.m_links[i];
    auto const &cache = g_caches[link.m_cache];
    if (cache.m_videos.count(video) != 0 ||
        cache.m_used + videoSize <= g_problem.m_capacity) {
      int currSavings = endpoint.m_serverLatency - link.m_latency;
      if (currSavings > bestSavings) {
        bestSavings = currSavings;
        bestLink = i;
      }
    }
  }

  return bestLink;
}

uint64_t GetSavings(Request const &request) {
  auto const &endpoint = g_problem.m_endpoints[request.m_endpoint];

  int link = GetBestLink(request);
  if (link < 0)
    return 0;

  uint64_t savings =
      endpoint.m_serverLatency - endpoint.m_links[link].m_latency;

  return savings * request.m_weight;
}

int main() {
  cin >> g_problem;

  vector<pair<int64_t, int>> requests;
  for (size_t i = 0; i < g_problem.m_requests.size(); ++i)
    requests.emplace_back(GetSavings(g_problem.m_requests[i]), i);

  sort(requests.rbegin(), requests.rend());
  for (size_t i = 0; i < requests.size(); ++i) {
    auto const &request = g_problem.m_requests[requests[i].second];
    int video = request.m_video;
    auto const &endpoint = g_problem.m_endpoints[request.m_endpoint];

    int link = GetBestLink(request);
    if (link < 0)
      continue;
    Cache &cache = g_caches[endpoint.m_links[link].m_cache];
    if (cache.m_videos.count(video) == 0) {
      cache.m_videos.insert(video);
      cache.m_used += g_problem.m_videos[video];
    }
  }

  Solution solution;
  solution.m_descriptions.resize(g_problem.m_numCaches);
  for (int i = 0; i < g_problem.m_numCaches; ++i) {
    auto &d = solution.m_descriptions[i];
    d.m_videos.assign(g_caches[i].m_videos.begin(), g_caches[i].m_videos.end());
    d.m_cache = i;
  }

  cout << solution;
  return 0;
}
