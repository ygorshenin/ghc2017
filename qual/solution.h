#pragma once

#include <iostream>
#include <vector>

struct Description {
  std::vector<int> m_videos;
  int m_cache;
};

struct Solution {
  std::vector<Description> m_descriptions;
};

std::ostream &operator<<(std::ostream &os, Description const &d);
std::ostream &operator<<(std::ostream &os, Solution const &s);
