#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

#include "Genetic_Algorithm.h"
#include "Parameters.h"

int test1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int test2[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};


void test_crossover()
{
    int test1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test2[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    CircuitF *parent1 = new CircuitF;
    parent1->sequence = test1;
    CircuitF *parent2 = new CircuitF;
    parent2->sequence = test2;

    crossover(*parent1, *parent2, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent1->sequence[i] == i);
        assert(parent2->sequence[i] == 15 - i);
    }

    // tracks if a crossover has taken place
    bool changed = false;

    crossover(*parent1, *parent2, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent1->sequence[i] != i + 1)
        {
            changed = true;
        }
    }
    assert(changed);

    delete parent1;
    delete parent2;
    int test3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test4[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    CircuitF *parent3 = new CircuitF;
    parent3->sequence = test3;
    CircuitF *parent4 = new CircuitF;
    parent4->sequence = test4;

    crossover2(*parent3, *parent4, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent3->sequence[i] == i);
        assert(parent4->sequence[i] == 15 - i);
    }

    // tracks if a crossover has taken place
    changed = false;

    crossover2(*parent3, *parent4, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent3->sequence[i] != i)
        {
            changed = true;
        }
    }
    assert(changed);

    delete parent3;
    delete parent4;
    int test5[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test6[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    CircuitF *parent5 = new CircuitF;
    parent5->sequence = test5;
    CircuitF *parent6 = new CircuitF;
    parent6->sequence = test6;

    crossoverR(*parent5, *parent6, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent5->sequence[i] == i);
        assert(parent6->sequence[i] == 15 - i);
    }

    // tracks if a crossover has taken place
    changed = false;

    crossoverR(*parent5, *parent6, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent5->sequence[i] != i)
        {
            changed = true;
        }
    }
    assert(changed);

    delete parent5;
    delete parent6;
    int test7[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test8[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    CircuitF *parent7 = new CircuitF;
    parent7->sequence = test7;
    CircuitF *parent8 = new CircuitF;
    parent8->sequence = test8;

    ensemble_crossover(*parent7, *parent8, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent7->sequence[i] == i);
        assert(parent8->sequence[i] == 15 - i);
    }

    // tracks if a crossover has taken place
    changed = false;

    ensemble_crossover(*parent7, *parent8, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent7->sequence[i] != i)
        {
            changed = true;
        }
    }
    assert(changed);
    delete parent7;
    delete parent8;
}

void test_mutate()
{
    int test1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test2[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    CircuitF *parent1 = new CircuitF;
    parent1->sequence = test1;

    mutate1(*parent1, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent1->sequence[i] == i);
    }

    // tracks if a crossover has taken place
    bool changed = false;

    mutate1(*parent1, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent1->sequence[i] != i + 1)
        {
            changed = true;
        }
    }
    assert(changed);

    delete parent1;
    int test3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test4[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    CircuitF *parent3 = new CircuitF;
    parent3->sequence = test3;

    mutate2(*parent3, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent3->sequence[i] == i);
    }

    // tracks if a crossover has taken place
    changed = false;

    mutate2(*parent3, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent3->sequence[i] != i)
        {
            changed = true;
        }
    }
    assert(changed);

    delete parent3;
    
    int test5[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test6[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    CircuitF *parent5 = new CircuitF;
    parent5->sequence = test5;

    mutate3(*parent5, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent5->sequence[i] == i);
    }

    // tracks if a crossover has taken place
    changed = false;

    mutate3(*parent5, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent5->sequence[i] != i)
        {
            changed = true;
        }
    }
    assert(changed);

    delete parent5;

    int test7[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int test8[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    CircuitF *parent7 = new CircuitF;
    parent7->sequence = test7;

    ensemble_mutate(*parent7, 0.0);

    for (int i = 0; i < 16; ++i)
    {
        assert(parent7->sequence[i] == i);
    }

    // tracks if a crossover has taken place
    changed = false;

    ensemble_mutate(*parent7, 1.0);

    for (int i = 0; i < 16; ++i)
    {
        if (parent7->sequence[i] != i)
        {
            changed = true;
        }
    }
    assert(changed);
    delete parent7;
}

int main()
{
    //test_crossover();
    test_mutate();
    return 0;
}
