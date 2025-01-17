/** Header for the unit class
 *
 *
 */

#ifndef CUNIT
#define CUNIT
#pragma once

class CUnit
{
public:
	// index of the unit to which this unit’s concentrate stream is connected
	int conc_num;
	// index of the unit to which this unit’s intermediate stream is connected
	int inter_num;
	// index of the unit to which this unit’s tailings stream is connected
	int tails_num;
	// A Boolean that is changed to true if the unit has been seen
	bool mark;
	// the index of the unit
	int num;


	//======================
	// input values (states)
	//======================

	double Fi_g;
	double Fi_w;


	double Fi_g_old;
	double Fi_w_old;


	//===============
	// output values
	//===============

	double C_g;
	double C_w;
	double I_g;
	double I_w;
	double T_g;
	double T_w;

	CUnit();
	// CUnit(int _num, int _conc_num, int _inter_num, int _tails_num);

	void update_output();
	void print_status();
	void initialise_parameters();

	void set_initial_guess(double _Fi_g, double _Fi_w);

	//=====================================
	// Validation Module Only:
	//=====================================
	// Setters for the unit connections
	void setConcNum(int num) { conc_num = num; }
	void setInterNum(int num) { inter_num = num; }
	void setTailsNum(int num) { tails_num = num; }

	// Getters for the unit connections
	int getConcNum() const { return conc_num; }
	int getInterNum() const { return inter_num; }
	int getTailsNum() const { return tails_num; }

	// Marking functions
	void setMark(bool value) { mark = value; }
	bool isMarked() const { return mark; }

private:

	//=================
	// constant values
	//=================

	double k_cg;
	double k_ig;
	double k_cw;
	double k_iw;
	double rho;
	double phi;
	double V;
	
	//====================
	// intermediate values
	//====================

	double t;
	double R_cg;
	double R_cw;
	double R_ig;
	double R_iw;
};
#endif