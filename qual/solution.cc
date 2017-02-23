#include "solution.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, Description const &d) {
  os << d.m_cache;
  for (auto v : d.m_videos) {
    os << " " << v;
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, Solution const &s) {
  os << s.m_descriptions.size() << endl;
  for (auto const &d : s.m_descriptions)
    os << d << endl;
  return os;
}
