
#include "CUnit.h"
#include "CCircuit.h"
#include "CSimulator.h"

using namespace std;


/**
 * @brief Evaluates the performance of a circuit based on the given parameters.
 * 
 * This function takes a circuit vector and returns a performance value.
 * It simulates the circuit operation, updating unit states in each iteration
 * until convergence or the maximum number of iterations is reached.
 * 
 * @param max_ites The maximum number of iterations to simulate.
 * @param threshold The threshold for convergence.
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector Pointer to the circuit vector.
 * @return The performance value of the circuit.
 */
double Evaluate_Circuit(int max_ites, double threshold, int vector_size, int *circuit_vector)

{
	// This function takes a circuit vector and returns a performance value.
	// The current version of the function is a dummy function that returns
	//  a performance value based on how close the circuit vector is to a predetermined answer vector.

	bool stop_simulation = true;

	//=========================================
	// 1- Set the initial guess
	//=========================================
	Circuit circuit(vector_size, circuit_vector);
	circuit.feed_g_circuit = 10;
	circuit.feed_w_circuit = 90;

// #pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < circuit.num_units; i++)
	{
		if (i == 0)
		{
			circuit.units[i].set_initial_guess(10, 90);
		}
		else
		{
			circuit.units[i].set_initial_guess(10, 90);
		}

		circuit.units[i].initialise_parameters();
	}

	int step = 0;
	for (; step < max_ites; step++)
	{
		// cout << step << endl;
		//===========================================
		// 2- For each unit, calculate the 6 outputs
		//===========================================
// #pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < circuit.num_units; i++)
		{
			circuit.units[i].update_output();
			// circuit.units[i].print_status();
		}

		//====================================================
		// 3- update the old feeds, and set current feed to 0
		//====================================================
// #pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < circuit.num_units; i++)
		{
			circuit.units[i].Fi_g_old = circuit.units[i].Fi_g;
			circuit.units[i].Fi_w_old = circuit.units[i].Fi_w;
			circuit.units[i].Fi_g = circuit.units[i].Fi_w = 0;
		}

		//========================================================
		// 4- Set the feed to the cell receiving the circuit feed
		// equal to the flow-rates of the circuit feed
		//========================================================
		circuit.units[circuit.entry_idx].Fi_g = circuit.feed_g_circuit;
		circuit.units[circuit.entry_idx].Fi_w = circuit.feed_w_circuit;

		//==========================================================
		// 5- add the concentrate & tailings to corresponding feeds
		//==========================================================
// #pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < circuit.num_units; i++)
		{
			// make sure dont access concentrate or tailing unit
			if(circuit.units[i].conc_num<circuit.num_units)
			{
				circuit.units[circuit.units[i].conc_num].Fi_g += circuit.units[i].C_g;
				circuit.units[circuit.units[i].conc_num].Fi_w += circuit.units[i].C_w;
			}

			if (circuit.units[i].inter_num < circuit.num_units){
				circuit.units[circuit.units[i].inter_num].Fi_g += circuit.units[i].I_g;
				circuit.units[circuit.units[i].inter_num].Fi_w += circuit.units[i].I_w;
			}

			if(circuit.units[i].tails_num < circuit.num_units){
				circuit.units[circuit.units[i].tails_num].Fi_g += circuit.units[i].T_g;
				circuit.units[circuit.units[i].tails_num].Fi_w += circuit.units[i].T_w;
			}

		}

		//====================================
		// 6- check the threshold to stop
		//====================================
		stop_simulation = true;
// #pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < circuit.num_units; i++)
		{
			// cout << circuit.units[i].Fi_g << circuit.units[i].Fi_g_old << endl;
			// if (abs(circuit.units[i].Fi_g - circuit.units[i].Fi_g_old) > threshold || abs(circuit.units[i].Fi_w - circuit.units[i].Fi_w_old) > threshold)
			if (abs((circuit.units[i].Fi_g - circuit.units[i].Fi_g_old) / circuit.units[i].Fi_g_old) > threshold || abs((circuit.units[i].Fi_w - circuit.units[i].Fi_w_old) / circuit.units[i].Fi_w_old) > threshold)
			{
				// #pragma omp critical
				// {
				stop_simulation = false;
				// }
			}
		}
		if (stop_simulation)
		{
			break;
		}
	}

	//===========================================
	// 7- Calculate metrics for the results
	//===========================================

	if (step >= max_ites - 1)
	{
		// cout << "[WARNING] Simulator: Did not converge." << endl;
		return -750 * circuit.feed_w_circuit;
	}

	double performance = calculate_performance(&circuit);
	double recovery = calculate_recovery(&circuit);
	double grade = calculate_grade(&circuit);

	std::ofstream outfile;
    outfile.open("post_processing/inputdata.txt");
    outfile << "Grade: " << grade << std::endl;
    outfile << "Recovery: " << recovery << std::endl;
    outfile.close();

	return performance;
}

/**
 * @brief Calculates the performance of a given circuit.
 * 
 * @param circuit Pointer to the Circuit object.
 * @return The calculated performance value.
 */
double calculate_performance(Circuit *circuit)
{
	double product_g = 0.0;
	double product_w = 0.0;

	for (int i = 0; i < circuit->num_units; i++)
	{
		if (circuit->units[i].conc_num == circuit->num_units)
		{
			product_g += circuit->units[i].C_g;
			product_w += circuit->units[i].C_w;
		}
		if (circuit->units[i].inter_num == circuit->num_units)
		{
			product_g += circuit->units[i].I_g;
			product_w += circuit->units[i].I_w;
		}
		if (circuit->units[i].tails_num == circuit->num_units)
		{
			product_g += circuit->units[i].T_g;
			product_w += circuit->units[i].T_w;
		}
	}

	return 100 * product_g - 750 * product_w;
}

/**
 * @brief Calculates the recovery rate of a given circuit.
 * 
 * @param circuit Pointer to the Circuit object.
 * @return The calculated recovery rate.
 */
double calculate_recovery(Circuit *circuit)
{
	double initial_feed_g = circuit->feed_g_circuit;
	double product_g = 0.0;

	for (int i = 0; i < circuit->num_units; i++)
	{
		if (circuit->units[i].conc_num == circuit->num_units)
		{
			product_g += circuit->units[i].C_g;
		}
	}
	double recovery = (product_g / initial_feed_g) * 100;
	return recovery;
}

/**
 * @brief Calculates the grade of the concentrate in a given circuit.
 * 
 * @param circuit Pointer to the Circuit object.
 * @return The calculated grade.
 */
double calculate_grade(Circuit *circuit)
{
	double total_concentrate_g = 0.0;
	double total_concentrate_mass = 0.0;
	for (int i = 0; i < circuit->num_units; i++)
	{
		if (circuit->units[i].conc_num == circuit->num_units)
		{
			total_concentrate_g += circuit->units[i].C_g;
			total_concentrate_mass += circuit->units[i].C_g + circuit->units[i].C_w;
		}
	}
	double grade = (total_concentrate_g / total_concentrate_mass) * 100;
	return grade;
}