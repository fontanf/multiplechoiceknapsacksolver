#pragma once

#include "multiplechoiceknapsacksolver/solution.hpp"

namespace multiplechoiceknapsacksolver
{

Output dynamic_programming_bellman_array(
        const Instance& instance,
        const Parameters& parameters = {});

Output dynamic_programming_bellman_array_all(
        const Instance& instance,
        const Parameters& parameters = {});

}
