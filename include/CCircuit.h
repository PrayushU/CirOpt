/** Header for the circuit class
 *
 * This header defines the circuit class and its associated functions
 *
*/

#ifndef CCIRCUIT
#define CCIRCUIT
#pragma once

#include <Parameters.h>
#include "CUnit.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <stdio.h>
#include <CUnit.h>

class Circuit {
  public:
    Circuit(int _vector_size, int *_circuit_vector);
    void populate_graph(int vector_size, int *circuit_vector);

    CUnit *units;

    int num_units; // this is calculated by the vector size.
    int entry_idx; // the index of the unit who receives the circuit feed.
    double feed_g_circuit; // the unit is kg/s
    double feed_w_circuit; // the unit is kg/s

    //=====================================
    // Validation Module Only:
    //=====================================
    // Constructor
    Circuit(int num_units);

    // Default destructor
    ~Circuit() = default;

    // Validation Module Only: Vector to hold units of the circuit
    std::vector<CUnit> val_units;
};

class Unit {
public:
    void setConcNum(int num) { concNum = num; }
    void setInterNum(int num) { interNum = num; }
    void setTailsNum(int num) { tailsNum = num; }
    void setMark(bool mark) { marked = mark; }
    int getConcNum() const { return concNum; }
    int getInterNum() const { return interNum; }
    int getTailsNum() const { return tailsNum; }
    bool isMarked() const { return marked; }

private:
    int concNum;
    int interNum;
    int tailsNum;
    bool marked;
};


bool mark_units(int unit_num, std::vector<Unit>& val_units, std::vector<bool>& canReachOutlet1, std::vector<bool>& canReachOutlet2);
bool Check_Validity(int vector_size, int* circuit_vector);

#endif