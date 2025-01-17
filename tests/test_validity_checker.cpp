#include "CCircuit.h"
#include "CUnit.h"
#include <iostream>

int main(int argc, char *argv[])
{

    auto performTest = [](bool result)
    {
        return result ? "failed" : "passed";
    };

    // Self-looping val_unit
    int self_ref_config[] = {0, 1, 0, 3, 1, 0, 4, 2, 1, 0}; // Unit 0 self-loops
    Circuit circuit_self_ref(3);
    bool isSelfRefValid = Check_Validity(sizeof(self_ref_config) / sizeof(self_ref_config[0]), self_ref_config);
    std::cout << "Self-looping val_unit test: " << performTest(isSelfRefValid) << std::endl;

    // Output out of bounds
    int out_of_bounds_config[] = {0, 1, 2, 6, 1, 0, 7, 2, 1, 0};
    Circuit circuit_out_of_bounds(3);
    bool isOutOfBoundsValid = Check_Validity(sizeof(out_of_bounds_config) / sizeof(out_of_bounds_config[0]), out_of_bounds_config);
    std::cout << "Output out of bounds test: " << performTest(isOutOfBoundsValid) << std::endl;

    // The destinations for the products from a val_unit should not all be the same val_unit
    int same_unit_config[] = {0, 1, 1, 1, 3, 0, 4, 2, 1, 0};
    Circuit circuit_same_unit(3);
    bool isSameUnit = Check_Validity(sizeof(same_unit_config) / sizeof(same_unit_config[0]), same_unit_config);
    std::cout << "Same Unit test: " << performTest(isSameUnit) << std::endl;

    // Tailings outlet reuse
    int tails_reuse_config[] = {0, 1, 2, 4, 3, 0, 0, 1, 0, 4};
    Circuit circuit_tails_reuse(3);
    bool isTailsReuseValid = Check_Validity(sizeof(tails_reuse_config) / sizeof(tails_reuse_config[0]), tails_reuse_config);
    std::cout << "Tailings outlet reuse test: " << performTest(isTailsReuseValid) << std::endl;

    // Incomplete val_unit outputs
    int incomplete_outputs_config[] = {0, 1, 2};
    Circuit circuit_incomplete_outputs(1);
    bool isIncompleteOutputsValid = Check_Validity(sizeof(incomplete_outputs_config) / sizeof(incomplete_outputs_config[0]), incomplete_outputs_config);
    std::cout << "Incomplete val_unit outputs test: " << performTest(isIncompleteOutputsValid) << std::endl;

    // No tailings outlet
    int no_tail_exit_config[] = {0, 1, 2, 2, 1, 1, 0, 2, 1, 3}; // No tailings outlet
    Circuit circuit_no_tail_exit(3);
    bool isNoTailExit = Check_Validity(sizeof(no_tail_exit_config) / sizeof(no_tail_exit_config[0]), no_tail_exit_config);
    std::cout << "No tailings outlet test: " << performTest(isNoTailExit) << std::endl;

    // Multiple same outlet
    int multiple_same_output_config[] = {0, 1, 2, 2, 3, 1, 0, 2, 4, 2}; // Repeated output to 2
    Circuit circuit_multiple_same_output(3);
    bool isMultipleSameOutput = Check_Validity(sizeof(multiple_same_output_config) / sizeof(multiple_same_output_config[0]), multiple_same_output_config);
    std::cout << "Multiple same outlet test: " << performTest(isMultipleSameOutput) << std::endl;

    // Single val_unit
    int single_unit_config[] = {0, 1, 1, 2}; // Only one val_unit
    Circuit circuit_single_unit(1);
    bool isSingleUnit = Check_Validity(sizeof(single_unit_config) / sizeof(single_unit_config[0]), single_unit_config);
    std::cout << "Single val_unit test: " << performTest(isSingleUnit) << std::endl;

    return 0;
}