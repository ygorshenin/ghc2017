cmake_minimum_required(VERSION 3.6)

project(Qual)

add_compile_options(
  "-std=c++11"
  "-Wall"
  )

add_library(common
  problem.cc
  problem.h
  solution.cc
  solution.h
  utils.cc
  utils.h
  )

add_executable(solver solver.cc)
add_executable(solver_m solver_m.cc)
add_executable(solver-y solver-y.cc)

add_custom_target(src.zip ALL COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "src.zip" --format=zip
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
  )

target_link_libraries(solver common)
target_link_libraries(solver_m common)
target_link_libraries(solver-y common)
