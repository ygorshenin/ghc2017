#include "solution.h"

#include <algorithm>
#include <cassert>
using namespace std;

std::ostream &operator<<(std::ostream &os, Description const &d) {
  os << d.m_cache;
  for (auto v : d.m_videos) {
    os << " " << v;
  }
  assert(is_sorted(d.m_videos.begin(), d.m_videos.end()));

  return os;
}

std::ostream &operator<<(std::ostream &os, Solution const &s) {
  os << s.m_descriptions.size() << endl;
  for (auto const &d : s.m_descriptions)
    os << d << endl;
  return os;
}

Solution::Solution(const std::vector<std::vector<int>> &videos) {
  m_descriptions.resize(videos.size());
  for (size_t i = 0; i < videos.size(); ++i) {
    m_descriptions[i].m_cache = i;
    m_descriptions[i].m_videos = videos[i];
  }
}
