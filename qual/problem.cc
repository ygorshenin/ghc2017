#include "problem.h"

std::istream &operator>>(std::istream &is, Link &link) {
  is >> link.m_cache >> link.m_latency;
  return is;
}

std::istream &operator>>(std::istream &is, Endpoint &endpoint) {
  int numLinks;
  is >> endpoint.m_serverLatency >> numLinks;

  endpoint.m_links.resize(numLinks);
  for (int i = 0; i < numLinks; ++i)
    is >> endpoint.m_links[i];
  return is;
}

std::istream &operator>>(std::istream &is, Request &request) {
  is >> request.m_video >> request.m_endpoint >> request.m_weight;
  return is;
}

std::istream &operator>>(std::istream &is, Problem &problem) {
  int numVideos;
  int numEndpoints;
  int numRequests;
  is >> numVideos >> numEndpoints >> numRequests >> problem.m_numCaches >>
      problem.m_capacity;

  problem.m_videos.resize(numVideos);
  for (int i = 0; i < numVideos; ++i)
    is >> problem.m_videos[i];

  problem.m_endpoints.resize(numEndpoints);
  for (int i = 0; i < numEndpoints; ++i)
    is >> problem.m_endpoints[i];

  problem.m_requests.resize(numRequests);
  for (int i = 0; i < numRequests; ++i)
    is >> problem.m_requests[i];

  return is;
}
