cmake_minimum_required(VERSION 3.6)

project(Practice)

add_compile_options(
  "-std=c++11"
  "-Wall"
  )

add_library(common
  candidate.cc
  candidate.h
  problem.cc
  problem.h
  )

add_executable(solver solver.cc)

target_link_libraries(solver common)
