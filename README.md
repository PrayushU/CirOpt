# CirOpt 
## Overview
 CirOpt is an advanced circuit simulation and optimization tool that leverages genetic algorithms to efficiently determine optimal circuit parameters. It is designed for researchers and engineers who require robust tools for electronic design automation (EDA).

## Directory Structure
```
CirOpt
│
├── .github/                # GitHub specific files like workflows
├── html/                   # HTML documentation
├── include/                # Header files for the project modules
│   ├── CCircuit.h
│   ├── CSimulator.h
│   ├── CUnit.h
│   ├── Genetic_Algorithm.h
│   └── Parameters.h
├── latex/                  # LaTeX documentation
├── plots/                  # Include output plots and results
│    └── sim_feedres.png
│    └── sim_units_vs_ites.png
│    └── sim_conv.png
│    └── nunits.png
│    └── murate.png
├── post_processing/        # Scripts and outputs for data post-processing
│   ├── outputs/            # Include GA Convergence plot and Circuit Graph
│   └── postprocessing.py
├── src/                    # Source files
│   ├── CCircuit.cpp        # Create and ensure the validity of a circuit configuration based on multiple units
│   ├── CSimulator.cpp      # Simulate and evaluate the performance of the circuit
│   ├── CUnit.cpp           # Simulate a unit operation within a processing system
│   ├── Genetic_Algorithm.cpp   # Genetic algorithm dedicated to the optimization of circuits
│   ├── main.cpp
│   └── CMakeLists.txt
├── tests/                  # Test cases and scripts
│   ├── test_circuit_simulator.cpp
│   ├── test_genetic_algorithm.cpp
│   ├── test_validity_checker.cpp
│   └── CMakeLists.txt
├── .gitignore              # Specifies intentionally untracked files to ignore
├── CMakeLists.txt          # Root CMake configuration file
├── Doxyfile                # Doxygen configuration file
├── evaluate_hpc.pbs            # PBS script for evaluation
├── gen_param.sh            # Script for generating parameters
├── local_run.sh            # Script to configure and run locally
├── LICENSE                 # License file
├── Problem Statement for Genetic Algorithm.pdf  # Problem statement document
└── README.md               # The README markdown file
```

## Features
- **Circuit Simulation**: Utilizes a custom simulator for circuit behavior.
- **Genetic Algorithm Optimization**: Employs genetic algorithms to optimize circuit configurations for predefined criteria.
- **Extensibility**: Easy to extend with more complex circuit components and optimization algorithms.
- **Testing Framework**: Includes a comprehensive set of tests for validation and verification of simulation logic and genetic algorithms.

## Getting Started
1. **Clone the Repository**
```
git clone [repository-url]
cd CirOpt
```

2. **Run Project**
```
./local_run.sh
```
another way for building directly in your terminal:
```
mkdir -p build
cd build
cmake .. 
make
./bin/Circuit_Optimizer
```

3. **Run Tests**
```
cd build
ctest -VV
```

## Results
The output of the simulations can be found in the `plots/` and `post_processing/outputs/` directory. `post_processing/outputs/` contains plot of GA Convergence and the final Circuit Graph, formatted in both graphical and text representations. `plots/` contains text files of the fitness results for different Crossover rate, Muration rate, number of Units and Population, and the plots of the trend of fitness against these variants.

## Dependencies
- CMake 3.10 or higher
- GCC 7.5.0 or higher
- Python 3.6 or higher (for post-processing)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
