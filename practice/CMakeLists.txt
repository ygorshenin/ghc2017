cmake_minimum_required(VERSION 3.6)

project(Practice)

add_compile_options(
  "-std=c++11"
  "-Wall"
  )

add_library(common
  candidate.cc
  candidate.h
  fenwick.h
  problem.cc
  problem.h
  )

add_executable(greedy-solver greedy-solver.cc)

target_link_libraries(greedy-solver common)
