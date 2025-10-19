#pragma once

#include "multiplechoiceknapsacksolver/instance.hpp"

#include <random>

namespace multiplechoiceknapsacksolver
{

Instance generate_uncorrelated(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator);

Instance generate_weakly_correlated(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator);

Instance generate_strongly_correlated(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator);

Instance generate_subset_sum(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator);

Instance generate_monotone(
        GroupId number_of_groups,
        ItemId number_of_items_in_groups,
        Weight data_range,
        double capacity_ratio,
        std::mt19937_64& generator);

}
