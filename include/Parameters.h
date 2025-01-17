#ifndef PARAM
#define PARAM
#include <iostream>

#pragma once

struct Algorithm_Parameters
{
    int max_generations;
    double crossover_rate;
    double mutation_rate;
};
static int NUM_CHILD=10;
static int NUM_UNIT=10;
static int POP_MULT=100;
static int THRESHOLD=100;
static int SIZE_CIRCUIT=3*NUM_UNIT +1;
#define DEFAULT_ALGORITHM_PARAMETERS \
    Algorithm_Parameters {1000, 0.8, 0.01}

#endif
