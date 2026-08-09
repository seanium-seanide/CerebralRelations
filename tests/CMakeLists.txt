add_executable(unit_tests)

target_sources(unit_tests
  PRIVATE
    unit_tests.cpp
)

target_compile_features(unit_tests
  PRIVATE
    cxx_std_23
)

target_link_libraries(unit_tests
  PRIVATE
    Catch2::Catch2WithMain
    CerebralRelationsLib
)

target_compile_options(unit_tests
  PRIVATE
    -Wall
    -Wextra
    -Werror
    -g
)

add_test(
  NAME unit_tests
  COMMAND unit_tests
)
