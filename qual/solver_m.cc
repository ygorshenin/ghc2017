#include "utils.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
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

  vector<vector<long long>> popularity(numCaches, vector<long long>(numVids));
  for (const auto &r : problem.m_requests) {
    const auto &e = problem.m_endpoints[r.m_endpoint];
    const int Ld = e.m_serverLatency;
    for (const auto &link : e.m_links) {
      const int L = link.m_latency;
      // todo: may overlap
      const auto h = (Ld - L) * static_cast<long long>(r.m_weight);
      popularity[link.m_cache][r.m_video] += h;
    }
  }

  vector<vector<int>> videos(numCaches);
  for (size_t i = 0; i < numCaches; ++i) {
    vector<vector<long long>> d(numVids + 1, vector<long long>(capacity + 1, -1));
    vector<vector<int>> prev(numVids + 1, vector<int>(capacity + 1, -1));
    d[0][0] = 0;
    for (int vid = 1; vid <= numVids; ++vid) {
      for (int prevVid = 0; prevVid < vid; ++prevVid) {
	for (int cap = 0; cap <= capacity; ++cap) {
	long long cur = d[prevVid][cap];
	if (cur < 0) {
	  continue;
	}
	int ncap = cap + problem.m_videos[vid - 1];
	if (ncap > capacity) {
	  continue;
	}
	cur += popularity[i][vid - 1];
	if (d[vid][ncap] < cur) {
	  d[vid][ncap] = cur;
	  prev[vid][ncap] = prevVid;
	}
      }
      }
    }
    int bestVid = 0;
    int bestCap = 0;
    for (int vid = 0; vid <= numVids; ++vid) {
      for (int cap = 0; cap <= capacity; ++cap) {
	if (d[bestVid][bestCap] < d[vid][cap]) {
	  bestVid = vid;
	  bestCap = cap;
	}
      }
    }
    int v = bestVid;
    int c = bestCap;
    while (v > 0) {
      int pv = prev[v][c];
      videos[i].push_back(v - 1);
      c -= problem.m_videos[v - 1];
      v = pv;
    }
    sort(videos.begin(), videos.end());
  }

  Solution solution(videos);
  cout << solution;
  cerr << "Score = " << CalculateScore(problem, solution) << endl;
  cerr << "Capacity = " << capacity << endl;
  return 0;
}
