/** header file for the circuit simulator
 * 
 * This header file defines the function that will be used to evaluate the circuit
*/
#ifndef CSIM
#define CSIM
#pragma once

#include <iostream>
#include "CCircuit.h"
#include "CUnit.h"
#include <cmath>
#include <iostream>
#include <fstream>

double Evaluate_Circuit(int max_ites, double threshold, int vector_size, int *circuit_vector);

double calculate_performance(Circuit* circuit);

double calculate_recovery(Circuit* circuit);

double calculate_grade(Circuit* circuit);
#endif