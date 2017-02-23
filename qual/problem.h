#pragma once

#include <iostream>
#include <vector>

struct Link {
  int m_cache;
  int m_latency;
};

struct Endpoint {
  int m_serverLatency;
  std::vector<Link> m_links;
};

struct Request {
  int m_video;
  int m_endpoint;
  int m_weight;
};

struct Problem {
  std::vector<int> m_videos;
  std::vector<Endpoint> m_endpoints;
  std::vector<Request> m_requests;

  int m_numCaches;
  int m_capacity;
};

std::istream &operator>>(std::istream &is, Link &link);
std::istream &operator>>(std::istream &is, Endpoint &endpoint);
std::istream &operator>>(std::istream &is, Request &request);
std::istream &operator>>(std::istream &is, Problem &problem);
