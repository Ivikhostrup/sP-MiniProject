add_library(doctest OBJECT doctest.cpp)

add_executable(tests test_reaction.cpp test_symbolTable.cpp $<TARGET_OBJECTS:doctest>)
target_link_libraries(tests stochasticsimulation_lib)

add_test(NAME tests COMMAND tests)
