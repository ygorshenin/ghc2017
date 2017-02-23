
#pragma once

#include <iostream>
#include <set>
#include <vector>

struct Description {
  std::vector<int> m_videos;
  int m_cache;
};

struct Solution {
  std::vector<Description> m_descriptions;

  Solution() = default;
  Solution(const std::vector<std::vector<int>> &videos);
  Solution(const std::vector<std::set<int>> &videos);
};

std::ostream &operator<<(std::ostream &os, Description const &d);
std::ostream &operator<<(std::ostream &os, Solution const &s);
