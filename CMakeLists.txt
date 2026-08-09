cmake_minimum_required(VERSION 3.25)
project(CerebralRelations VERSION 1.0.0 LANGUAGES CXX)

set(BUILD_TESTING "Build unit tests" ON)
set(CEREBRALRELATIONS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include(FetchPackages.cmake)

add_subdirectory(source)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
