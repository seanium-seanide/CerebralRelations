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


add_executable(CerebralRelations)

target_sources(CerebralRelations
  PRIVATE
    main.cpp
)

target_link_libraries(CerebralRelations
  PRIVATE
    CerebralRelationsLib
)
