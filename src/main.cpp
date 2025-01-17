#include <iostream>
#include <ctime>  // Include for time function

#include "CUnit.h"
#include "CCircuit.h"
#include "CSimulator.h"
#include "Genetic_Algorithm.h"
#include "Parameters.h"
#include <cmath>





    



int main(int argc, char *argv[])
{
    srand(time(NULL));
    bool verbose = false;
    CircuitF** Children = allocate_gen2(NUM_CHILD);
    CircuitF** Parents = allocate_gen2(NUM_CHILD);
    init_gen0(Parents); // we get the parents since we select the best

    // Variables to keep track of the best individual
    CircuitF* best_individual = nullptr;
    std::vector<double> best_fitnesses;
    double best_fitness = -1.0; // Assuming fitness values are positive
    
    int iter_num=0;
    for (int i = 1; i <= DEFAULT_ALGORITHM_PARAMETERS.max_generations; ++i){
        // print i
        if(verbose){
            std::cout << "========================" << std::endl;
            std::cout << "Generation: " << i << std::endl;
            std::cout << "========================" << std::endl;
        }

        evolve_step(Parents, Children, DEFAULT_ALGORITHM_PARAMETERS);

        if(verbose){
            for (int j = 0; j < NUM_CHILD; ++j){ // NUM_CHILD
                std::cout << "Child " << j+1 << " fitness: " << Children[j]->fitness_value << std::endl;
            }
        }

        // Check for the best individual in the current generation
        if (Children[0]->fitness_value > best_fitness){
            iter_num = 0;
            best_fitness = Children[0]->fitness_value;
            best_fitnesses.push_back(best_fitness);
            best_individual = Children[0];
        }else if ((int)Children[0]->fitness_value == (int)best_fitness) {
        // Increment only if the integer parts of the fitness values are equal
            iter_num++;
            //THRESHOLD is the minimum number of iteration the fitness values has to stay stable
            if (iter_num >= THRESHOLD) {
                if(verbose)
                    // std::cerr << "Value converged after iter: " << iter_num << std::endl;
                break;  // Exit the loop if it has happened 10 times
            }
        }

        // Swap parents and children
        CircuitF** temp = Parents;
        Parents = Children;
        Children = temp;

        // Set the best individual as the first parent
        Parents[0]->sequence = best_individual->sequence;
        Parents[0]->fitness_value = best_individual->fitness_value;

        // std::cout << std::endl;
    }

    // Print the best individual found
    if (best_individual != nullptr) {
        std::cout << "========================" << std::endl;
        std::cout << "Best Individual Found: " << std::endl;
        std::cout << "Sequence: ";
        for (int i = 0; i < SIZE_CIRCUIT; ++i){
            std::cout << best_individual->sequence[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Fitness: " << best_individual->fitness_value << std::endl;
        std::cout << "========================" << std::endl;
    }

    

    
    Circuit solution(3*NUM_UNIT+1, best_individual->sequence);
    float grade = calculate_grade(&solution);
    float recovery = calculate_recovery(&solution);
    std::ofstream outfile;
        outfile.open("post_processing/inputdata.txt", std::ios::app);
    outfile <<"Num units: "<< NUM_UNIT<< std::endl;
    outfile << "Performance: " << best_individual->fitness_value << std::endl;
    outfile <<"Vector: ";
    for (int i = 0; i < SIZE_CIRCUIT; ++i)
        {
            outfile << best_individual->sequence[i] << " ";
        }
    outfile << std::endl;
    outfile <<"Fitnesses: ";
    for (int i = 0; i < best_fitnesses.size(); ++i)
        {
            outfile << best_fitnesses[i] << " ";
        }
    outfile << std::endl;
    outfile.close();
    system("python post_processing/postprocessing.py");
    return 0;
}