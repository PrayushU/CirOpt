#include "Genetic_Algorithm.h"


// Function to allocate memory for chromosomes
CircuitF **allocate_gen2(int num_child) {
  int *data = new int[num_child * SIZE_CIRCUIT];
  CircuitF *chrom_array = new CircuitF[num_child];
  CircuitF **array = new CircuitF *[num_child];

  for (int i = 0; i < num_child; ++i) {
    array[i] = &chrom_array[i];
    array[i]->sequence = &data[i * SIZE_CIRCUIT];
  }
  return array;
}

// Function to deallocate memory for chromosomes
void free_gen2(CircuitF **array) {
  delete[] array[0]->sequence; // Free the data array
  delete[] array[0];          // Free the CircuitF array
  delete[] array;             // Free the pointer array
}

// Function to initialize a chromosome
void init_chromosome(CircuitF &chromosome) {
  chromosome.sequence[0] = 0;
  bool valid_chromosome = false;

  while (!valid_chromosome) {
    for (int i = 0; i < NUM_UNIT; ++i) {
      chromosome.sequence[3 * i + 1] = rand() % NUM_UNIT;
      while (chromosome.sequence[3 * i + 1] == i) {
        chromosome.sequence[3 * i + 1] = rand() % NUM_UNIT;
      }

      chromosome.sequence[3 * i + 2] = rand() % NUM_UNIT;
      while (chromosome.sequence[3 * i + 2] == i ||
             chromosome.sequence[3 * i + 2] == chromosome.sequence[3 * i + 1]) {
        chromosome.sequence[3 * i + 2] = rand() % NUM_UNIT;
      }

      chromosome.sequence[3 * i + 3] = rand() % NUM_UNIT;
      while (chromosome.sequence[3 * i + 3] == i ||
             chromosome.sequence[3 * i + 3] == chromosome.sequence[3 * i + 1] ||
             chromosome.sequence[3 * i + 3] == chromosome.sequence[3 * i + 2]) {
        chromosome.sequence[3 * i + 3] = rand() % NUM_UNIT;
      }
      // output streams
      chromosome.sequence[3 * NUM_UNIT - 2] = NUM_UNIT; // conc
      chromosome.sequence[3 * (NUM_UNIT - 1)] = NUM_UNIT + 1; // waste

    }

    valid_chromosome = Check_Validity(SIZE_CIRCUIT, chromosome.sequence); // FIX
  }

  chromosome.fitness_value = Evaluate_Circuit(1e4, 1.0e-6, SIZE_CIRCUIT, chromosome.sequence);
  
}

// Function to save the population to a file
void grid_to_file(CircuitF **generation, int gen_num) {
  std::stringstream fname1;
  std::ofstream f1;

  fname1 << "gen_" << gen_num << ".gen";
  f1.open(fname1.str().c_str(), std::ios::out);

  for (int i = 0; i < NUM_CHILD; i++) {
    for (int j = 0; j < SIZE_CIRCUIT; j++) {
      f1 << generation[i]->sequence[j] << "\t";
    }
    f1 << std::endl;
  }

  f1.close();
}


void crossover(CircuitF &parent1, CircuitF &parent2, double crossover_rate) {
    double random_cross = ((double)rand()) / RAND_MAX;
    if (random_cross < crossover_rate) {
        int crossover_point = 1 + (rand() % (SIZE_CIRCUIT)); // dont touch last two units
        for (int j = crossover_point; j < SIZE_CIRCUIT; ++j) {
            std::swap(parent1.sequence[j], parent2.sequence[j]);
        }
    }
}

void crossover2(CircuitF &parent1, CircuitF &parent2, double crossover_rate) {
  double random_cross = ((double)rand()) / RAND_MAX;
  if (random_cross < crossover_rate) {
      int crossover_point1 = 1 + (rand() % (3 * NUM_UNIT));
      int crossover_point2 = 1 + (rand() % (3 * NUM_UNIT));
      if (crossover_point2 < crossover_point1)
          std::swap(crossover_point1, crossover_point2);
      for (int j = crossover_point1; j < crossover_point2; ++j) {
          std::swap(parent1.sequence[j], parent2.sequence[j]);
      }
  }
}

void crossoverR(CircuitF &parent1, CircuitF &parent2, double crossover_rate) {
    double random_cross = ((double)rand()) / RAND_MAX;
    if (random_cross < crossover_rate) {
        for (int j = 1; j < SIZE_CIRCUIT; ++j) {
            if (j % 3 != 1) {
                if (rand() % 2 == 0) {
                    std::swap(parent1.sequence[j], parent2.sequence[j]);
                }
            }
        }
    }
}


void ensemble_crossover(CircuitF& parent1, CircuitF& parent2, double crossover_rate) {
    int choice = rand() % 3;  // Randomly select between 0, 1, or 2

    switch (choice) {
        case 0:
            crossover(parent1, parent2, crossover_rate);
            break;
        case 1:
            crossover2(parent1, parent2, crossover_rate);
            break;
        case 2:
            crossoverR(parent1, parent2, crossover_rate);
            break;
    }
}

void mutate1(CircuitF &circuit, double mutation_rate) {
  //print mut rate
  for (int j = 1; j < SIZE_CIRCUIT; j++) {
    double random_mu = ((double)rand()) / RAND_MAX;
    if (random_mu < mutation_rate && j != 3 * NUM_UNIT && j != 3 * (NUM_UNIT - 1) && j != 0) {
      circuit.sequence[j] = rand() % NUM_UNIT;
    } 
  }
}

void mutate2(CircuitF &circuit, double mutation_rate) {
  int start_index = 3;
    int end_index = 3 * (NUM_UNIT - 1);
    int group_size = 3;
    
    for (int j = start_index; j < end_index; j += group_size) {
        double random_mu = ((double)rand()) / RAND_MAX;
        if (random_mu < mutation_rate) {
            for (int k = 0; k < group_size / 2; k++) {
                int temp = circuit.sequence[j + k];
                circuit.sequence[j + k] = circuit.sequence[j + group_size - 1 - k];
                circuit.sequence[j + group_size - 1 - k] = temp;
            }
        }
    }
}

void mutate3(CircuitF &circuit, double mutation_rate) {
  //print mut rate
  int start_index = 3;
    int end_index = 3 * (NUM_UNIT - 1);
    int group_size = 3;
    
    for (int j = start_index; j < end_index; j += group_size) {
        double random_mu = ((double)rand()) / RAND_MAX;
        if (random_mu < mutation_rate) {
            bool insertion = (rand() % 2 == 0);
            
            if (insertion) {
                int new_element = rand() % NUM_UNIT;
                for (int k = group_size - 1; k > 0; k--) {
                    circuit.sequence[j + k] = circuit.sequence[j + k - 1];
                }
                circuit.sequence[j] = new_element;
            } else {
                int delete_index = j + (rand() % group_size);
                for (int k = delete_index; k < j + group_size - 1; k++) {
                    circuit.sequence[k] = circuit.sequence[k + 1];
                }
            }
        }
    }
}

void ensemble_mutate(CircuitF& circuit, double mutation_rate) {
    int choice = rand() % 3;  // Randomly select between 0, 1, or 2

    switch (choice) {
        case 0:
            mutate1(circuit, mutation_rate);
            break;
        case 1:
            mutate2(circuit, mutation_rate);
            break;
        case 2:
            mutate3(circuit, mutation_rate);
            break;
    }
}





int evolve_step(CircuitF** Parents, CircuitF** Children, struct Algorithm_Parameters parameters) {
    int num_pool = NUM_CHILD * (NUM_CHILD - 1);
    CircuitF** Pool = allocate_gen2(num_pool);
    int valid_count = 0;
    int invalid_count = 0;

    // Generate the pool of chromosomes
    int pool_idx = 0;
    for (int i = 0; i < NUM_CHILD - 1; ++i) {
        for (int j = i + 1; j < NUM_CHILD; ++j) {
            // Copy sequences from parents to pool
            std::copy(Parents[i]->sequence, Parents[i]->sequence + SIZE_CIRCUIT, Pool[pool_idx]->sequence);
            std::copy(Parents[j]->sequence, Parents[j]->sequence + SIZE_CIRCUIT, Pool[pool_idx + 1]->sequence);
            // Perform crossover between Parents[i] and Parents[j]
            // crossover(*Pool[pool_idx], *Pool[pool_idx + 1], parameters.crossover_rate);
            // crossover2(*Pool[pool_idx], *Pool[pool_idx + 1], parameters.crossover_rate);
            // crossoverR(*Pool[pool_idx], *Pool[pool_idx + 1], parameters.crossover_rate);
            ensemble_crossover(*Pool[pool_idx], *Pool[pool_idx + 1], parameters.crossover_rate);
            
            // Perform mutation
            mutate1(*Pool[pool_idx], parameters.mutation_rate);
            mutate1(*Pool[pool_idx + 1], parameters.mutation_rate);

            // Check 1
            if (Check_Validity(SIZE_CIRCUIT, Pool[pool_idx]->sequence)) { // Valid
                Pool[pool_idx]->fitness_value = Evaluate_Circuit(1e4, 1.0e-6, SIZE_CIRCUIT, Pool[pool_idx]->sequence);
                valid_count++;
            } else {
                Pool[pool_idx]->fitness_value = -1e3;
                invalid_count++;
            }

            // Check 2
            if (Check_Validity(SIZE_CIRCUIT, Pool[pool_idx + 1]->sequence)) { // Valid
                Pool[pool_idx + 1]->fitness_value = Evaluate_Circuit(1e4, 1.0e-6, SIZE_CIRCUIT, Pool[pool_idx + 1]->sequence);
                valid_count++;
            } else {
                Pool[pool_idx + 1]->fitness_value = -1e3;
                invalid_count++;
            }

            pool_idx += 2;
        }
    }

    // Check the fitness of the pool and store the best NUM_CHILD in children
    std::vector<std::pair<double, int>> fitness_indices;
    for (int i = 0; i < num_pool; ++i) {
        fitness_indices.push_back(std::make_pair(Pool[i]->fitness_value, i));
    }

    // Sort the fitness indices based on fitness values in descending order
    std::sort(fitness_indices.begin(), fitness_indices.end(), std::greater<>());

    // Copy the top NUM_CHILD chromosomes to the Children array
    for (int i = 0; i < NUM_CHILD; ++i) {
        int best_idx = fitness_indices[i].second;
        std::copy(Pool[best_idx]->sequence, Pool[best_idx]->sequence + SIZE_CIRCUIT, Children[i]->sequence);
        Children[i]->fitness_value = Pool[best_idx]->fitness_value;
    }

    free_gen2(Pool);

    // Print the number of valid and invalid sequences
    // std::cerr << "Valid Offsprings: " << valid_count << " Invalid Offsprings: " << invalid_count << std::endl;
    
    return 0;
}



void init_gen0(CircuitF** Children, int pop_multiplier) {
    // Allocate memory for the initial parent and children populations
    int num_parent = pop_multiplier * NUM_CHILD;
    CircuitF** Parents = allocate_gen2(num_parent); // keep 10 times the number of children
    // CircuitF** Children = allocate_gen2(NUM_CHILD);

    // Initialize the parent chromosomes
    for (int i = 0; i < num_parent; ++i) {
        init_chromosome(*Parents[i]); // parallelized 10x
    }

    // Check the fitness of the parents and store the best 10 in children
    std::vector<std::pair<double, int>> fitness_indices;
    for (int i = 0; i < num_parent; ++i) {
        fitness_indices.push_back(std::make_pair(Parents[i]->fitness_value, i));
    }

    // Sort the fitness indices based on fitness values in descending order
    std::sort(fitness_indices.begin(), fitness_indices.end(), std::greater<>());

    // Copy the top NUM_CHILD chromosomes to the Children array
    for (int i = 0; i < NUM_CHILD; ++i) {
        int best_idx = fitness_indices[i].second;
        std::copy(Parents[best_idx]->sequence, Parents[best_idx]->sequence + SIZE_CIRCUIT, Children[i]->sequence);
        Children[i]->fitness_value = Parents[best_idx]->fitness_value;
    }

    // Deallocate memory for Parents
    delete[] Parents[0]->sequence; // Free the data array
    delete[] Parents[0];           // Free the CircuitF array
    delete[] Parents;              // Free the pointer array
    // print gen 0 sampled
    // fprintf(stderr, "Generation 0 sampled\n\n");
}
