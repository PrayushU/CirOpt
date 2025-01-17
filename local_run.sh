#!/bin/bash


crossover_rates=(0.8)
mutation_rates=(0.01)
num_children=(10)
num_units=(10)
pop_mults=(100)
threshold=100
# Fixed value for max_generations
max_generations=1000
./gen_param.sh "$max_generations" "${crossover_rates[0]}" "${mutation_rates[0]}" \
                    "${num_children[0]}" "${num_units[0]}" "${pop_mults[0]}" "$threshold"

mkdir -p build
pushd build
cd build 

cmake ..

make 

popd


echo "Running ./build/bin/Circuit_Optimizer"
./build/bin/Circuit_Optimizer

