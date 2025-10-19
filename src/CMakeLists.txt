add_library(MultipleChoiceKnapsackSolver)
target_sources(MultipleChoiceKnapsackSolver PRIVATE
    instance.cpp
    instance_builder.cpp
    solution.cpp
    algorithm_formatter.cpp)
target_include_directories(MultipleChoiceKnapsackSolver PUBLIC
    ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(MultipleChoiceKnapsackSolver PUBLIC
    OptimizationTools::utils)
add_library(MultipleChoiceKnapsackSolver ALIAS MultipleChoiceKnapsackSolver)

add_subdirectory(algorithms)

if(MULTIPLECHOICEKNAPSACKSOLVER_BUILD_MAIN)
    add_executable(MultipleChoiceKnapsackSolver_main)
    target_sources(MultipleChoiceKnapsackSolver_main PRIVATE
        main.cpp)
    target_link_libraries(MultipleChoiceKnapsackSolver_main PUBLIC
        MultipleChoiceKnapsackSolver_milp
        MultipleChoiceKnapsackSolver_dyer_zemel
        MultipleChoiceKnapsackSolver_dynamic_programming_bellman
        Boost::program_options)
    set_target_properties(MultipleChoiceKnapsackSolver_main PROPERTIES OUTPUT_NAME "multiplechoiceknapsacksolver")
    install(TARGETS MultipleChoiceKnapsackSolver_main)
endif()

add_library(MultipleChoiceKnapsackSolver_generator)
target_sources(MultipleChoiceKnapsackSolver_generator PRIVATE
    generator.cpp)
target_link_libraries(MultipleChoiceKnapsackSolver_generator PUBLIC
    MultipleChoiceKnapsackSolver)
add_library(MultipleChoiceKnapsackSolver::generator ALIAS MultipleChoiceKnapsackSolver_generator)

if(MULTIPLECHOICEKNAPSACKSOLVER_BUILD_MAIN)
    add_executable(MultipleChoiceKnapsackSolver_generator_main)
    target_sources(MultipleChoiceKnapsackSolver_generator_main PRIVATE
        generator_main.cpp)
    target_link_libraries(MultipleChoiceKnapsackSolver_generator_main PUBLIC
        MultipleChoiceKnapsackSolver_generator
        Boost::program_options)
    set_target_properties(MultipleChoiceKnapsackSolver_generator_main PROPERTIES OUTPUT_NAME "multiplechoiceknapsacksolver_generator")
    install(TARGETS MultipleChoiceKnapsackSolver_generator_main)
endif()
