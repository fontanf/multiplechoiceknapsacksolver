#include "multiplechoiceknapsacksolver/generator.hpp"

#include "multiplechoiceknapsacksolver/instance_builder.hpp"

using namespace multiplechoiceknapsacksolver;

Instance multiplechoiceknapsacksolver::generate_uncorrelated(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;

    // Add items.
    Weight weight_max = 0;
    Weight weight_sum = 0;
    std::uniform_int_distribution<Weight> distribution(1, data_range);
    for (GroupId group_id = 0; group_id < number_of_groups; ++group_id) {
        Weight group_weight_max = 0;
        for (ItemId pos = 0; pos < number_of_items_in_groups; ++pos) {
            Weight weight = distribution(generator);
            Profit profit = distribution(generator);
            instance_builder.add_item(group_id, profit, weight);

            weight_max = std::max(weight_max, weight);
            group_weight_max = std::max(group_weight_max, weight);
        }
        weight_sum += group_weight_max;
    }

    // Compute capacity.
    Weight capacity = std::max(
            weight_max,
            (Weight)(capacity_ratio * weight_sum));
    instance_builder.set_capacity(capacity);

    return instance_builder.build();
}

Instance multiplechoiceknapsacksolver::generate_weakly_correlated(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;

    // Add items.
    Weight weight_max = 0;
    Weight weight_sum = 0;
    std::uniform_int_distribution<Weight> distribution_weight(1, data_range);
    std::uniform_int_distribution<Profit> distribution_profit(-10, 10);
    for (GroupId group_id = 0; group_id < number_of_groups; ++group_id) {
        Weight group_weight_max = 0;
        for (ItemId pos = 0; pos < number_of_items_in_groups; ++pos) {
            Weight weight = distribution_weight(generator);
            Profit profit = std::max((Profit)1, weight + distribution_profit(generator));
            instance_builder.add_item(group_id, profit, weight);

            weight_max = std::max(weight_max, weight);
            group_weight_max = std::max(group_weight_max, weight);
        }
        weight_sum += group_weight_max;
    }

    // Compute capacity.
    Weight capacity = std::max(
            weight_max,
            (Weight)(capacity_ratio * weight_sum));
    instance_builder.set_capacity(capacity);

    return instance_builder.build();
}

Instance multiplechoiceknapsacksolver::generate_strongly_correlated(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;

    // Add items.
    Weight weight_max = 0;
    Weight weight_sum = 0;
    std::uniform_int_distribution<Weight> distribution_weight(1, data_range);
    for (GroupId group_id = 0; group_id < number_of_groups; ++group_id) {
        Weight group_weight_max = 0;
        for (ItemId pos = 0; pos < number_of_items_in_groups; ++pos) {
            Weight weight = distribution_weight(generator);
            Profit profit = weight + 10;
            instance_builder.add_item(group_id, profit, weight);

            weight_max = std::max(weight_max, weight);
            group_weight_max = std::max(group_weight_max, weight);
        }
        weight_sum += group_weight_max;
    }

    // Compute capacity.
    Weight capacity = std::max(
            weight_max,
            (Weight)(capacity_ratio * weight_sum));
    instance_builder.set_capacity(capacity);

    return instance_builder.build();
}

Instance multiplechoiceknapsacksolver::generate_subset_sum(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;

    // Add items.
    Weight weight_max = 0;
    Weight weight_sum = 0;
    std::uniform_int_distribution<Weight> distribution_weight(1, data_range);
    for (GroupId group_id = 0; group_id < number_of_groups; ++group_id) {
        Weight group_weight_max = 0;
        for (ItemId pos = 0; pos < number_of_items_in_groups; ++pos) {
            Weight weight = distribution_weight(generator);
            Profit profit = weight;
            instance_builder.add_item(group_id, profit, weight);

            weight_max = std::max(weight_max, weight);
            group_weight_max = std::max(group_weight_max, weight);
        }
        weight_sum += group_weight_max;
    }

    // Compute capacity.
    Weight capacity = std::max(
            weight_max,
            (Weight)(capacity_ratio * weight_sum));
    instance_builder.set_capacity(capacity);

    return instance_builder.build();
}

Instance multiplechoiceknapsacksolver::generate_monotone(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator)
{
    InstanceBuilder instance_builder;

    // Add items.
    Weight weight_max = 0;
    Weight weight_sum = 0;
    std::uniform_int_distribution<Weight> distribution(1, data_range);
    for (GroupId group_id = 0; group_id < number_of_groups; ++group_id) {
        Weight group_weight_max = 0;
        std::vector<Weight> weights;
        std::vector<Profit> profits;
        for (ItemId pos = 0; pos < number_of_items_in_groups; ++pos) {
            weights.push_back(distribution(generator));
            profits.push_back(distribution(generator));
        }
        std::sort(weights.begin(), weights.end());
        std::sort(profits.rbegin(), profits.rend());
        for (ItemId pos = 0; pos < number_of_items_in_groups; ++pos) {
            Weight weight = weights[pos];
            Profit profit = profits[pos];
            instance_builder.add_item(group_id, profit, weight);

            weight_max = std::max(weight_max, weight);
            group_weight_max = std::max(group_weight_max, weight);
        }
        weight_sum += group_weight_max;
    }

    // Compute capacity.
    Weight capacity = std::max(
            weight_max,
            (Weight)(capacity_ratio * weight_sum));
    instance_builder.set_capacity(capacity);

    return instance_builder.build();
}
