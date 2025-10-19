#include "multiplechoiceknapsacksolver/algorithms/milp.hpp"

#include "multiplechoiceknapsacksolver/algorithm_formatter.hpp"

using namespace multiplechoiceknapsacksolver;

namespace
{

mathoptsolverscmake::MilpModel create_milp_model(
        const Instance& instance)
{
    int number_of_variables = instance.number_of_items();
    int number_of_constraints = 1 + instance.number_of_groups();
    int number_of_elements = 3 * instance.number_of_items();

    mathoptsolverscmake::MilpModel model(
            number_of_variables,
            number_of_constraints,
            number_of_elements);

    // Variable and objective.
    model.objective_direction = mathoptsolverscmake::ObjectiveDirection::Maximize;
    for (ItemId item_id = 0;
            item_id < instance.number_of_items();
            ++item_id) {
        const Item& item = instance.item(item_id);
        model.variables_lower_bounds[item_id] = 0;
        model.variables_upper_bounds[item_id] = 1;
        model.variables_types[item_id] = mathoptsolverscmake::VariableType::Binary;
        model.objective_coefficients[item_id] = item.profit;
    }

    // Constraints.
    int element_id = 0;
    int constraints_id = 0;

    // Constraint: knapsack constraint.
    model.constraints_starts[constraints_id] = element_id;
    for (ItemId item_id = 0;
            item_id < instance.number_of_items();
            ++item_id) {
        const Item& item = instance.item(item_id);
        model.elements_variables[element_id] = item_id;
        model.elements_coefficients[element_id] = item.weight;
        element_id++;
    }
    model.constraints_upper_bounds[constraints_id] = instance.capacity();
    constraints_id++;

    // Constraints:conflict constraints.
    for (GroupId group_id = 0;
            group_id < instance.number_of_groups();
            ++group_id) {
        const Group& group = instance.group(group_id);
        model.constraints_starts[constraints_id] = element_id;
        for (const ItemId item_id: group.item_ids) {
            model.elements_variables[element_id] = item_id;
            model.elements_coefficients[element_id] = 1.0;
            element_id++;
        }
        model.constraints_upper_bounds[constraints_id] = 1;
        constraints_id++;
    }

    return model;
}

Solution retrieve_solution(
        const Instance& instance,
        const std::vector<double>& milp_solution)
{
    Solution solution(instance);
    for (ItemId item_id = 0;
            item_id < instance.number_of_items();
            ++item_id) {
        if (milp_solution[item_id] > 0.5)
            solution.add(item_id);
    }
    return solution;
}

}

MilpOutput multiplechoiceknapsacksolver::milp(
        const Instance& instance,
        const MilpParameters& parameters)
{
    MilpOutput output(instance);
    AlgorithmFormatter algorithm_formatter(parameters, output);
    algorithm_formatter.start("MILP");

    algorithm_formatter.print_header();

    mathoptsolverscmake::MilpModel milp_model = create_milp_model(instance);
    std::vector<double> milp_solution;
    double milp_bound = std::numeric_limits<double>::infinity();

    if (parameters.solver == mathoptsolverscmake::SolverName::Highs) {
#ifdef HIGHS_FOUND
        Highs highs;
        mathoptsolverscmake::reduce_printout(highs);
        mathoptsolverscmake::set_time_limit(highs, parameters.timer.remaining_time());
        mathoptsolverscmake::set_log_file(highs, "highs.log");
        mathoptsolverscmake::load(highs, milp_model);
        highs.setCallback([
                &instance,
                &parameters,
                &output,
                &algorithm_formatter](
                    const int,
                    const std::string& message,
                    const HighsCallbackOutput* highs_output,
                    HighsCallbackInput* highs_input,
                    void*)
                {
                    // Retrieve solution.
                    double milp_objective_value = highs_output->mip_primal_bound;
                    if (output.solution.profit() < milp_objective_value) {
                        Solution solution = retrieve_solution(instance, highs_output->mip_solution);
                        algorithm_formatter.update_solution(solution, "");
                    }

                    // Retrieve bound.
                    double milp_bound = highs_output->mip_dual_bound;
                    if (milp_bound != std::numeric_limits<double>::infinity()) {
                        Profit bound = std::floor(milp_bound + 1e-5);
                        algorithm_formatter.update_bound(bound, "");
                    }

                    // Check end.
                    if (parameters.timer.needs_to_end())
                        highs_input->user_interrupt = 1;
                },
                nullptr);
        HighsStatus highs_status = highs.startCallback(HighsCallbackType::kCallbackMipImprovingSolution);
        mathoptsolverscmake::solve(highs);
        milp_solution = mathoptsolverscmake::get_solution(highs);
        milp_bound = mathoptsolverscmake::get_bound(highs);
#else
        throw std::invalid_argument("");
#endif

    } else {
        throw std::invalid_argument("");
    }

    // Retrieve solution.
    Solution solution = retrieve_solution(instance, milp_solution);
    algorithm_formatter.update_solution(solution, "");

    // Retrieve bound.
    if (milp_bound != std::numeric_limits<double>::infinity()) {
        Profit bound = std::floor(milp_bound + 1e-5);
        algorithm_formatter.update_bound(milp_bound, "");
    }

    algorithm_formatter.end();
    return output;
}
