function(CerebralRelations_addScenario)
  cmake_parse_arguments(
    ARG
    ""
    "SCENARIO_NAME;RESULT_REGEX"
    "SCENARIO_COMMAND"
    ${ARGN}
  )

  add_test(NAME ${ARG_SCENARIO_NAME} COMMAND ${ARG_SCENARIO_COMMAND})
  set_tests_properties(${ARG_SCENARIO_NAME} PROPERTIES PASS_REGULAR_EXPRESSION "${ARG_RESULT_REGEX}")
endfunction()


CerebralRelations_addScenario(
  SCENARIO_NAME     CerebralRelationsApp_InvalidInput
  SCENARIO_COMMAND  CerebralRelations 1 2 3
  RESULT_REGEX      "Usage"
)

CerebralRelations_addScenario(
  SCENARIO_NAME     CerebralRelationsApp_EmptyInput
  SCENARIO_COMMAND  CerebralRelations ${CMAKE_CURRENT_SOURCE_DIR}/assets/scripts/empty.bf
  RESULT_REGEX      ""
)

CerebralRelations_addScenario(
  SCENARIO_NAME     CerebralRelationsApp_Hello
  SCENARIO_COMMAND  CerebralRelations ${CMAKE_CURRENT_SOURCE_DIR}/assets/scripts/hello_world_verbose.bf
  RESULT_REGEX      "Hello World!"
)
