#include "tests.hpp"
#include "multiplechoiceknapsacksolver/algorithms/milp.hpp"

using namespace multiplechoiceknapsacksolver;

TEST_P(ExactAlgorithmTest, ExactAlgorithm)
{
    TestParams test_params = GetParam();
    const Instance instance = get_instance(test_params.files);
    const Solution solution = get_solution(instance, test_params.files);
    auto output = test_params.algorithm(instance);
    std::cout << std::endl;
    std::cout << "Refence solution" << std::endl;
    std::cout << "----------------" << std::endl;
    solution.format(std::cout, 1);
    EXPECT_EQ(output.value, solution.profit());
    EXPECT_EQ(output.value, output.solution.profit());
    EXPECT_EQ(output.bound, solution.profit());
}

INSTANTIATE_TEST_SUITE_P(
        MultipleChoiceKnapsackMilp,
        ExactAlgorithmTest,
        testing::ValuesIn(get_test_params(
                {
                    [](const Instance& instance)
                    {
                        return milp(instance);
                    },
                },
                {
                    get_test_instance_paths(get_path({"data", "test_milp.txt"})),
                })));
