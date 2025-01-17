#include <CCircuit.h>


/**
 * @brief Constructor for the Circuit class.
 * 
 * Initializes the Circuit object with the given vector size and circuit vector.
 * 
 * @param _vector_size The size of the circuit vector.
 * @param _circuit_vector Pointer to the circuit vector.
 */
Circuit::Circuit(int _vector_size, int *_circuit_vector)
{

	if ((_vector_size - 1) % 3 != 0)
	{
		std::cout << "[ERROR] Circuit: unexpected graph vector size: " << _vector_size << std::endl;
		exit(0);
	}

	num_units = (_vector_size - 1) / 3;

	units = new CUnit[num_units];

	entry_idx = -1;
	feed_g_circuit = 10;
	feed_w_circuit = 90;
	populate_graph(_vector_size, _circuit_vector);
}

/**
 * @brief Populates the graph with units based on the provided circuit vector.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector Pointer to the circuit vector.
 */
void Circuit::populate_graph(int vector_size, int *circuit_vector)
{
	if (vector_size != 3 * num_units + 1)
	{
		std::cout << "[ERROR] Circuit: unexpected number of units: " << vector_size << "," << num_units << std::endl;
		exit(0);
	}

	entry_idx = circuit_vector[0];

	int current_unit_idx = -1;
	for (int i = 1; i < vector_size;)
	{
		current_unit_idx = (i - 1) / 3;

		units[current_unit_idx].conc_num = circuit_vector[i++];
		units[current_unit_idx].inter_num = circuit_vector[i++];
		units[current_unit_idx].tails_num = circuit_vector[i++];
		units[current_unit_idx].num = current_unit_idx;
	}
}

// Vectors to mark whether each unit can reach each of the two outlets
std::vector<bool> canReachOutlet1;
std::vector<bool> canReachOutlet2;

/**
 * @brief Constructor initializes the vector of CUnits to the correct size.
 * 
 * @param num_units The number of units in the circuit.
 */
Circuit::Circuit(int num_units)
{
	val_units.resize(num_units);
	canReachOutlet1.resize(num_units, false);
	canReachOutlet2.resize(num_units, false);
}

bool mark_units(int unit_num, std::vector<Unit>& val_units, std::vector<bool>& canReachOutlet1, std::vector<bool>& canReachOutlet2);

/**
 * @brief Checks the validity of the given circuit vector.
 * 
 * @param vector_size The size of the circuit vector.
 * @param circuit_vector Pointer to the circuit vector.
 * @return true if the circuit vector is valid, false otherwise.
 */
bool Check_Validity(int vector_size, int* circuit_vector) {
    std::vector<Unit> val_units(NUM_UNIT);
    std::vector<bool> canReachOutlet1(NUM_UNIT, false);
    std::vector<bool> canReachOutlet2(NUM_UNIT, false);

    if (vector_size != SIZE_CIRCUIT) {
        return false;
    }

    int count_conc_n = 0;
    int count_tail_n1 = 0;

    for (int i = 0; i < NUM_UNIT; ++i) {
        val_units[i].setConcNum(circuit_vector[3 * i + 1]);
        val_units[i].setInterNum(circuit_vector[3 * i + 2]);
        val_units[i].setTailsNum(circuit_vector[3 * i + 3]);
        val_units[i].setMark(false);

        if (val_units[i].getConcNum() == NUM_UNIT)
          count_conc_n++;


        if (val_units[i].getTailsNum() == NUM_UNIT + 1)
            count_tail_n1++;

        if (val_units[i].getConcNum() < 0 || val_units[i].getConcNum() > NUM_UNIT + 1 ||
            val_units[i].getInterNum() < 0 || val_units[i].getInterNum() > NUM_UNIT + 1 ||
            val_units[i].getTailsNum() < 0 || val_units[i].getTailsNum() > NUM_UNIT + 1 ||
            val_units[i].getConcNum() == i || val_units[i].getInterNum() == i || val_units[i].getTailsNum() == i ||
            (val_units[i].getConcNum() == val_units[i].getInterNum() && val_units[i].getInterNum() == val_units[i].getTailsNum())) {
            return false;
        }
    }

    if (count_conc_n != 1 || count_tail_n1 != 1) {
        return false;
    }

    if (!mark_units(circuit_vector[0], val_units, canReachOutlet1, canReachOutlet2)) {
        return false;
    }

    for (int i = 0; i < NUM_UNIT; ++i) {
        if (!val_units[i].isMarked()) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Marks units that can reach the outlets.
 * 
 * @param unit_num The current unit number.
 * @param val_units Vector of units in the circuit.
 * @param canReachOutlet1 Vector indicating if units can reach outlet 1.
 * @param canReachOutlet2 Vector indicating if units can reach outlet 2.
 * @return true if the marking is successful, false otherwise.
 */
bool mark_units(int unit_num, std::vector<Unit>& val_units, std::vector<bool>& canReachOutlet1, std::vector<bool>& canReachOutlet2) {
    if (val_units[unit_num].isMarked())
        return true;

    val_units[unit_num].setMark(true);

    if (val_units[unit_num].getConcNum() == val_units.size() + 1 || val_units[unit_num].getTailsNum() == val_units.size()) {
        return false;
    }

    if (val_units[unit_num].getInterNum() == val_units.size() || val_units[unit_num].getInterNum() == val_units.size() + 1) {
        return false;
    }

    bool valid = true;

    if (val_units[unit_num].getConcNum() == val_units.size()) {
        canReachOutlet1[unit_num] = true;
    } else if (val_units[unit_num].getConcNum() == val_units.size() + 1) {
        canReachOutlet2[unit_num] = true;
    } else if (val_units[unit_num].getConcNum() < val_units.size()) {
        valid &= mark_units(val_units[unit_num].getConcNum(), val_units, canReachOutlet1, canReachOutlet2);
    }

    if (val_units[unit_num].getInterNum() == val_units.size()) {
        canReachOutlet1[unit_num] = true;
    } else if (val_units[unit_num].getInterNum() == val_units.size() + 1) {
        canReachOutlet2[unit_num] = true;
    } else if (val_units[unit_num].getInterNum() < val_units.size()) {
        valid &= mark_units(val_units[unit_num].getInterNum(), val_units, canReachOutlet1, canReachOutlet2);
    }

    if (val_units[unit_num].getTailsNum() == val_units.size()) {
        canReachOutlet1[unit_num] = true;
    } else if (val_units[unit_num].getTailsNum() == val_units.size() + 1) {
        canReachOutlet2[unit_num] = true;
    } else if (val_units[unit_num].getTailsNum() < val_units.size()) {
        valid &= mark_units(val_units[unit_num].getTailsNum(), val_units, canReachOutlet1, canReachOutlet2);
    }

    return valid;
}

