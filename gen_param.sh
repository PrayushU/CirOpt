#!/bin/bash

# Check for correct number of arguments
if [ "$#" -ne 7 ]; then
    echo "Usage: $0 max_generations crossover_rate mutation_rate num_children num_units pop_mult"
    exit 1
fi

# Assign command line arguments to variables
max_generations=$1
crossover_rate=$2
mutation_rate=$3
num_children=$4
num_units=$5
pop_mult=$6
threshold=$7 # Fixed value, modify if needed

# Generate parameter.h
cat > include/Parameters.h <<EOF
#ifndef PARAM
#define PARAM
#include <iostream>

#pragma once

struct Algorithm_Parameters
{
    int max_generations;
    double crossover_rate;
    double mutation_rate;
    // other parameters for your algorithm
};
static int NUM_CHILD=$num_children;
static int NUM_UNIT=$num_units;
static int POP_MULT=$pop_mult;
static int THRESHOLD=$threshold;
static int SIZE_CIRCUIT=3*NUM_UNIT +1;
#define DEFAULT_ALGORITHM_PARAMETERS \\
    Algorithm_Parameters {$max_generations, $crossover_rate, $mutation_rate}

#endif
EOF

echo "Generated Parameters.h with max_generations=$max_generations, crossover_rate=$crossover_rate, mutation_rate=$mutation_rate, NUM_CHILD=$num_children, NUM_UNIT=$num_units, POP_MULT=$pop_mult, THRESHOLD=$threshold, SIZE_CIRCUIT=$size_circuit"

