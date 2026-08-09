add_executable(unit_tests)

target_sources(unit_tests
  PRIVATE
    unit_tests.cpp
)

target_link_libraries(unit_tests
  PRIVATE
    Catch2::Catch2WithMain
    CerebralRelationsLib
)

add_test(
  NAME unit_tests
  COMMAND unit_tests
)
