#include "tests.hpp"
#include "multiplechoiceknapsacksolver/algorithms/dynamic_programming_bellman.hpp"

using namespace multiplechoiceknapsacksolver;

TEST_P(ExactAlgorithmTest, ExactAlgorithm)
{
    TestParams test_params = GetParam();
    const Instance instance = get_instance(test_params.files);
    const Solution solution = get_solution(instance, test_params.files);
    auto output = test_params.algorithm(instance);
    EXPECT_EQ(output.value, solution.profit());
    EXPECT_EQ(output.value, output.solution.profit());
    EXPECT_EQ(output.bound, solution.profit());
}

TEST_P(ExactNoSolutionAlgorithmTest, ExactNoSolutionAlgorithm)
{
    TestParams test_params = GetParam();
    const Instance instance = get_instance(test_params.files);
    const Solution solution = get_solution(instance, test_params.files);
    auto output = test_params.algorithm(instance);
    EXPECT_EQ(output.value, solution.profit());
    EXPECT_EQ(output.bound, solution.profit());
}

INSTANTIATE_TEST_SUITE_P(
        MultipleChoiceKnapsackDynamicProgrammingBellmanArray,
        ExactNoSolutionAlgorithmTest,
        testing::ValuesIn(get_test_params(
                {
                    [](const Instance& instance)
                    {
                        return dynamic_programming_bellman_array(instance);
                    },
                },
                {
                    get_test_instance_paths(get_path({"data", "test_dynamic_programming_bellman_array_all.txt"})),
                })));

INSTANTIATE_TEST_SUITE_P(
        MultipleChoiceKnapsackDynamicProgrammingBellmanNoSolution,
        ExactNoSolutionAlgorithmTest,
        testing::ValuesIn(get_test_params(
                {
                    [](const Instance& instance)
                    {
                        return dynamic_programming_bellman_array_all(instance);
                    },
                },
                {
                    get_test_instance_paths(get_path({"data", "test_dynamic_programming_bellman_array_all.txt"})),
                })));
