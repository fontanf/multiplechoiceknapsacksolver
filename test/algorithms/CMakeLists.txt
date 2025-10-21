add_library(MultipleChoiceKnapsackSolver_tests)
target_sources(MultipleChoiceKnapsackSolver_tests PRIVATE
    tests.cpp)
target_link_libraries(MultipleChoiceKnapsackSolver_tests PUBLIC
    MultipleChoiceKnapsackSolver
    Boost::filesystem
    GTest::gtest_main)
add_library(MultipleChoiceKnapsackSolver::tests ALIAS MultipleChoiceKnapsackSolver_tests)

add_executable(MultipleChoiceKnapsackSolver_dynamic_programming_bellman_test)
target_sources(MultipleChoiceKnapsackSolver_dynamic_programming_bellman_test PRIVATE
    dynamic_programming_bellman_test.cpp)
target_link_libraries(MultipleChoiceKnapsackSolver_dynamic_programming_bellman_test
    MultipleChoiceKnapsackSolver_tests
    MultipleChoiceKnapsackSolver_dynamic_programming_bellman
    GTest::gtest_main)
gtest_discover_tests(MultipleChoiceKnapsackSolver_dynamic_programming_bellman_test
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    PROPERTIES TIMEOUT 3600)

add_executable(MultipleChoiceKnapsackSolver_milp_test)
target_sources(MultipleChoiceKnapsackSolver_milp_test PRIVATE
    milp_test.cpp)
target_link_libraries(MultipleChoiceKnapsackSolver_milp_test
    MultipleChoiceKnapsackSolver_tests
    MultipleChoiceKnapsackSolver_milp
    GTest::gtest_main)
gtest_discover_tests(MultipleChoiceKnapsackSolver_milp_test
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    PROPERTIES TIMEOUT 3600)

add_executable(MultipleChoiceKnapsackSolver_dyer_zemel_test)
target_sources(MultipleChoiceKnapsackSolver_dyer_zemel_test PRIVATE
    dyer_zemel_test.cpp)
target_link_libraries(MultipleChoiceKnapsackSolver_dyer_zemel_test
    MultipleChoiceKnapsackSolver_tests
    MultipleChoiceKnapsackSolver_dyer_zemel
    GTest::gtest_main)
gtest_discover_tests(MultipleChoiceKnapsackSolver_dyer_zemel_test
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    PROPERTIES TIMEOUT 3600)
