function(CerebralRelations_addTest)
  cmake_parse_arguments(
    ARG
    ""
    "TEST_NAME;TEST_SOURCE"
    "LINK_LIBRARIES"
    ${ARGN}
  )

  add_executable(${ARG_TEST_NAME})
  target_sources(${ARG_TEST_NAME} PRIVATE ${ARG_TEST_SOURCE})
  target_compile_features(${ARG_TEST_NAME} PRIVATE cxx_std_23)
  target_link_libraries(${ARG_TEST_NAME} PRIVATE Catch2::Catch2WithMain ${ARG_LINK_LIBRARIES})
  target_compile_options(${ARG_TEST_NAME} PRIVATE -Wall -Wextra -Werror -g)
endfunction()


CerebralRelations_addTest(
  TEST_NAME UtilitiesLibUnitTests
  TEST_SOURCE UtilitiesLibUnitTests.cpp
  LINK_LIBRARIES
    UtilitiesLib
)

CerebralRelations_addTest(
  TEST_NAME CerebralRelationsLibUnitTests
  TEST_SOURCE CerebralRelationsLibUnitTests.cpp
  LINK_LIBRARIES
    CerebralRelationsLib
)

CerebralRelations_addTest(
  TEST_NAME CerebralRelationsLibIntegrationTests
  TEST_SOURCE CerebralRelationsLibIntegrationTests.cpp
  LINK_LIBRARIES
    CerebralRelationsLib
    UtilitiesLib
)
