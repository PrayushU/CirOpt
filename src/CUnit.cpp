#include "CUnit.h"
#include <iostream>

/**
 * @brief Constructor for the CUnit class.
 * 
 * Initializes unit parameters and sets default values for unit connections and state.
 */
CUnit::CUnit()
{
    conc_num = -1;
    inter_num = -1;
    tails_num = -1;
    num = -1;
    mark = false;
    initialise_parameters();
}

/**
 * @brief Sets the initial guess for the input flow rates.
 * 
 * @param _Fi_g Initial guess for the gold feed flow rate.
 * @param _Fi_w Initial guess for the waste feed flow rate.
 */
void CUnit::set_initial_guess(double _Fi_g, double _Fi_w)
{
    //======================
    // input values (states)
    //======================

    Fi_g = _Fi_g;
    Fi_w = _Fi_w;

    Fi_g_old = 99999;
    Fi_w_old = 99999;
}

/**
 * @brief Initializes the unit parameters.
 * 
 * Sets the default values for the output flow rates, reaction constants, and physical properties.
 */
void CUnit::initialise_parameters()
{

    //===============
    // output values
    //===============

    C_g = 0;
    C_w = 0;
    I_g = 0;
    I_w = 0;
    T_g = 0;
    T_w = 0;

    //=================
    // constant values
    //=================

    k_cg = 0.004;  // unit: kg/s^-1
    k_ig = 0.001;  // unit: kg/s^-1
    k_cw = 0.0002; // unit: kg/s^-1
    k_iw = 0.0003; // unit: kg/s^-1

    rho = 3000; // unit: kg/m^3
    phi = 0.1;  // this is %
    V = 10;     // unit: m^3

    //====================
    // intermediate values
    //====================

    t = 0;
    R_cg = 0;
    R_cw = 0;
    R_ig = 0;
    R_iw = 0;
}

/**
 * @brief Updates the output flow rates based on the current input flow rates and reaction constants.
 */
void CUnit::update_output()
{
    //============================
    // Update intermediate values
    //============================
    t = (phi * V * rho) / (Fi_g + Fi_w);
    R_cg = (t * k_cg) / (t * (k_cg + k_ig) + 1);
    R_cw = (t * k_cw) / (t * (k_cw + k_iw) + 1);
    R_ig = (t * k_ig) / (t * (k_cg + k_ig) + 1);
    R_iw = (t * k_iw) / (t * (k_cw + k_iw) + 1);

    //===================
    // calculate outputs
    //===================

    C_g = Fi_g * R_cg;
    C_w = Fi_w * R_cw;
    I_g = Fi_g * R_ig;
    I_w = Fi_w * R_iw;
    T_g = Fi_g * (1 - R_cg - R_ig);
    T_w = Fi_w * (1 - R_cw - R_iw);
}

/**
 * @brief Prints the current status of the unit.
 * 
 * Outputs the unit number, connections, input flow rates, reaction constants, and output flow rates.
 */
void CUnit::print_status()
{
    std::cout << "================================================" << std::endl;
    std::cout << "Unit #" << num << ":" << std::endl;

    std::cout << "Next node (con, int, tal): "<<conc_num<<' '<<inter_num<<' '<<tails_num<<std::endl;

    std::cout << "Fig, Fiw: " << Fi_g << ' ' << Fi_w << std::endl;
    std::cout << "Rcg, Rcw, Rig, Riw: " << R_cg << ' ' << R_cw << ' ' << R_ig << ' ' << R_iw << std::endl;
    std::cout << "Cg, Cw, Ig, Iw, Tg, Tw: " << C_g << ' ' << C_w << ' ' << I_g << ' ' << I_w << ' ' << T_g << ' ' << T_w << std::endl;
    std::cout << "================================================" << std::endl;
}