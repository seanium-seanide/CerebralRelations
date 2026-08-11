###########################
# UtilitiesLib unit tests #
###########################

add_executable(UtilitiesLibUnitTests)

target_sources(UtilitiesLibUnitTests
  PRIVATE
    UtilitiesLibUnitTests.cpp
)

target_compile_features(UtilitiesLibUnitTests
  PRIVATE
    cxx_std_23
)

target_link_libraries(UtilitiesLibUnitTests
  PRIVATE
    UtilitiesLib
    Catch2::Catch2WithMain
)

target_compile_options(UtilitiesLibUnitTests
  PRIVATE
    -Wall
    -Wextra
    -Werror
    -g
)

add_test(
  NAME    UtilitiesLibUnitTests
  COMMAND UtilitiesLibUnitTests
)

###################################
# CerebralRelationsLib unit tests #
###################################

add_executable(CerebralRelationsLibUnitTests)

target_sources(CerebralRelationsLibUnitTests
  PRIVATE
    CerebralRelationsLibUnitTests.cpp
)

target_compile_features(CerebralRelationsLibUnitTests
  PRIVATE
    cxx_std_23
)

target_link_libraries(CerebralRelationsLibUnitTests
  PRIVATE
    CerebralRelationsLib
    Catch2::Catch2WithMain
)

target_compile_options(CerebralRelationsLibUnitTests
  PRIVATE
    -Wall
    -Wextra
    -Werror
    -g
)

add_test(
  NAME    CerebralRelationsLibUnitTests
  COMMAND CerebralRelationsLibUnitTests
)

##########################################
# CerebralRelationsLib integration tests #
##########################################

add_executable(CerebralRelationsLibIntegrationTests)

target_sources(CerebralRelationsLibIntegrationTests
  PRIVATE
    CerebralRelationsLibIntegrationTests.cpp
)

target_compile_features(CerebralRelationsLibIntegrationTests
  PRIVATE
    cxx_std_23
)

target_link_libraries(CerebralRelationsLibIntegrationTests
  PRIVATE
    CerebralRelationsLib
    UtilitiesLib
    Catch2::Catch2WithMain
)

target_compile_options(CerebralRelationsLibIntegrationTests
  PRIVATE
    -Wall
    -Wextra
    -Werror
    -g
)

add_test(
  NAME              CerebralRelationsLibIntegrationTests
  COMMAND           CerebralRelationsLibIntegrationTests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
