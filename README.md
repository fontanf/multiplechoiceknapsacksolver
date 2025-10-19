# MultipleChoiceKnapsackSolver

A solver for the multiple-choice knapsack problems:

## Implemented algorithms

* Mixed-integer linear programming `--algorithm milp`

* Dynamic programming
  * Bellman
    * Array (only optimal value) `-a dynamic-programming-bellman-array`
    * Array (all) `-a dynamic-programming-bellman-array-all`

## Usage

### Command line

Compile:
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
cmake --install build --config Release --prefix install
```

Download data:
```shell
python3 scripts/download_data.py
```

Solve an instance:
```shell
./install/bin/multiplechoiceknapsacksolver  --verbosity-level 1  --input ./data/strongly_correlated/g10_ni10_r1000/instance_g10_ni10_r1000_c50  --algorithm dynamic-programming-bellman-array-all  --certificate solution.txt
```

Run tests:
```shell
ctest --parallel --output-on-failure  --test-dir build/test
```
