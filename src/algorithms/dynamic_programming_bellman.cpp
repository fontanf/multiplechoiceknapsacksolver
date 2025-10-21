#include "multiplechoiceknapsacksolver/algorithms/dynamic_programming_bellman.hpp"

#include "multiplechoiceknapsacksolver/algorithm_formatter.hpp"

using namespace multiplechoiceknapsacksolver;

////////////////////////////////////////////////////////////////////////////////
////////////////////// dynamic_programming_bellman_array ///////////////////////
////////////////////////////////////////////////////////////////////////////////

Output multiplechoiceknapsacksolver::dynamic_programming_bellman_array(
        const Instance& instance,
        const Parameters& parameters)
{
    Output output(instance);
    AlgorithmFormatter algorithm_formatter(parameters, output);
    algorithm_formatter.start("Dynamic programming - Bellman - array");
    algorithm_formatter.print_header();

    std::vector<Profit> values_prev(instance.capacity() + 1, 0);
    std::vector<Profit> values_next(instance.capacity() + 1, 0);
    Weight weight_sum = 0;
    for (GroupId group_id = 0; group_id < instance.number_of_groups(); ++group_id) {
        // Check time
        if (parameters.timer.needs_to_end()) {
            algorithm_formatter.end();
            return output;
        }

        // Update DP table
        values_prev = values_next;
        Weight weight_max = 0;
        Weight weight_min = instance.capacity();
        for (ItemId item_id: instance.group(group_id).item_ids) {
            weight_max = std::max(weight_max, instance.item(item_id).weight);
            weight_min = std::min(weight_min, instance.item(item_id).weight);
        }
        weight_sum += weight_max;
        for (Weight weight = std::min(instance.capacity(), weight_sum);
                weight >= weight_min;
                --weight) {
            for (ItemId item_id: instance.group(group_id).item_ids) {
                const Item& item = instance.item(item_id);
                if (weight - item.weight >= 0
                        && values_next[weight] < values_prev[weight - item.weight] + item.profit) {
                    values_next[weight] = values_prev[weight - item.weight] + item.profit;
                }
            }
        }
    }

    // Retrieve best value.
    Profit value = 0;
    for (Weight weight = instance.capacity(); weight >= 0; --weight)
        value = (std::max)(value, values_next[weight]);
    // Update value.
    algorithm_formatter.update_value(
            value,
            "algorithm end");
    // Update bound.
    algorithm_formatter.update_bound(
            value,
            "algorithm end");

    algorithm_formatter.end();
    return output;
}

namespace
{

inline StateId compute_state_id(
        const Instance& instance,
        GroupId group_id,
        Weight weight)
{
    return (group_id + 1) * (instance.capacity() + 1) + weight;
}

}

Output multiplechoiceknapsacksolver::dynamic_programming_bellman_array_all(
        const Instance& instance,
        const Parameters& parameters)
{
    Output output(instance);
    AlgorithmFormatter algorithm_formatter(parameters, output);
    algorithm_formatter.start("Dynamic programming - Bellman - array - store all states");
    algorithm_formatter.print_header();

    // Initialize memory table
    StateId values_size = (instance.number_of_groups() + 1) * (instance.capacity() + 1);
    std::vector<Profit> values(values_size, 0);

    Weight weight_sum = 0;
    for (GroupId group_id = 0; group_id < instance.number_of_groups(); ++group_id) {
        // Check time
        if (parameters.timer.needs_to_end()) {
            algorithm_formatter.end();
            return output;
        }

        // Update DP table
        Weight weight_max = 0;
        Weight weight_min = instance.capacity();
        for (ItemId item_id: instance.group(group_id).item_ids) {
            weight_max = std::max(weight_max, instance.item(item_id).weight);
            weight_min = std::min(weight_min, instance.item(item_id).weight);
        }
        weight_sum += weight_max;
        for (Weight weight = std::min(instance.capacity(), weight_sum);
                weight >= weight_min;
                --weight) {
            StateId state_1_id = compute_state_id(instance, group_id - 1, weight);
            StateId state_2_id = compute_state_id(instance, group_id, weight);
            values[state_2_id] = values[state_1_id];
            for (ItemId item_id: instance.group(group_id).item_ids) {
                const Item& item = instance.item(item_id);
                if (weight - item.weight >= 0) {
                    StateId state_1_id = compute_state_id(instance, group_id - 1, weight - item.weight);
                    if (values[state_2_id] < values[state_1_id] + item.profit)
                        values[state_2_id] = values[state_1_id] + item.profit;
                }
            }
        }
    }

    // Retrieve best value.
    Profit value_best = 0;
    Weight weight_best = 0;
    for (Weight weight = instance.capacity(); weight >= 0; --weight) {
        StateId state_id = compute_state_id(instance, instance.number_of_groups() - 1, weight);
        if (value_best < values[state_id]) {
            value_best = values[state_id];
            weight_best = weight;
        }
    }

    // Update upper bound
    algorithm_formatter.update_bound(
            value_best,
            "algorithm end (bound)");

    // Retrieve optimal solution.
    Weight weight = weight_best;
    Solution solution(instance);
    for (GroupId group_id = instance.number_of_groups() - 1;
            group_id >= 0;
            --group_id) {
        const Group& group = instance.group(group_id);
        StateId state_id = compute_state_id(instance, group_id, weight);
        for (ItemId item_id: group.item_ids) {
            const Item& item = instance.item(item_id);
            if (weight - item.weight < 0)
                continue;
            StateId state_prev_id = compute_state_id(instance, group_id - 1, weight - item.weight);
            if (values[state_prev_id] + item.profit == values[state_id]) {
                weight -= item.weight;
                solution.add(item_id);
                break;
            }
        }
    }
    algorithm_formatter.update_solution(
            solution,
            "algorithm end (solution)");

    algorithm_formatter.end();
    return output;
}
