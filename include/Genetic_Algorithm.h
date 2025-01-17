/** Header for the Genetic Algorithm library
 *
 */

#ifndef GEN_ALGO
#define GEN_ALGO
#pragma once
#include <Parameters.h>
#include "CCircuit.h"
#include "CSimulator.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct CircuitF {
  int *sequence;
  double fitness_value;
};

CircuitF **allocate_gen2(int num_child);
void init_gen0(CircuitF** Children, int pop_multiplier = POP_MULT);

int evolve_step(CircuitF** Parents, CircuitF** Children, 
                struct Algorithm_Parameters parameters = DEFAULT_ALGORITHM_PARAMETERS);
void crossover(CircuitF &parent1, CircuitF &parent2, double crossover_rate);
void crossover2(CircuitF &parent1, CircuitF &parent2, double crossover_rate);
void crossoverR(CircuitF &parent1, CircuitF &parent2, double crossover_rate);
void ensemble_crossover(CircuitF& parent1, CircuitF& parent2, double crossover_rate);
void mutate1(CircuitF &circuit, double mutation_rate);
void mutate2(CircuitF &circuit, double mutation_rate);
void mutate3(CircuitF &circuit, double mutation_rate);
void ensemble_mutate(CircuitF &circuit, double mutation_rate);

#endif