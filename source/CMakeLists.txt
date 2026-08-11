################
# UtilitiesLib #
################

add_library(UtilitiesLib)

target_sources(UtilitiesLib
  PRIVATE
    utilities.cpp

  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS
        ${CEREBRALRELATIONS_INCLUDE_DIR}
      FILES
        ${CEREBRALRELATIONS_INCLUDE_DIR}/utilities.hpp
)

target_compile_features(UtilitiesLib
  PRIVATE
    cxx_std_23
)

########################
# CerebralRelationsLib #
########################

add_library(CerebralRelationsLib)

target_sources(CerebralRelationsLib
  PRIVATE
    CerebralRelations.cpp

  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS
        ${CEREBRALRELATIONS_INCLUDE_DIR}
      FILES
        ${CEREBRALRELATIONS_INCLUDE_DIR}/CerebralRelations.hpp
)

target_compile_features(CerebralRelationsLib
  PRIVATE
    cxx_std_23
)

target_link_libraries(CerebralRelationsLib
  PRIVATE
    fmt::fmt
)

#####################
# CerebralRelations #
#####################

add_executable(CerebralRelations)

target_sources(CerebralRelations
  PRIVATE
    main.cpp
)

target_compile_features(CerebralRelations
  PRIVATE
    cxx_std_23
)

target_link_libraries(CerebralRelations
  PRIVATE
    CerebralRelationsLib
)
