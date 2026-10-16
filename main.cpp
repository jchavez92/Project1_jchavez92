#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "struct_capacitor.h"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void runConstCurrent(double dt, int num_steps, double i, Capacitor &amps)  //function for constant current simulation
{
    double v_now = 0.0;  //voltage variable at t=0 is initiated to 0V
    amps.time[0] =  0.0; //assigning initial t=0
    amps.voltage[0] = v_now;  //assigning initial voltage to v_now
    amps.current[0] = i;  //assigning initial current to constant value i

    for (int j = 1; j < num_steps + 1; j++)  //loop for number of timesteps
    {
        double v_next = v_now + (i * dt * (1.0 / amps.C)); //adds previous voltage to next voltage
        // N/A???   double dv_dt = (v_next - v_now) / dt;  //change in voltage over duration dt

        amps.time[j] = dt * j;  //assigning time index j to dt * j
        amps.voltage[j] = v_next;  //assigning voltage index j to present value v_next
        amps.current[j] = i;  //assigning current index j to constant value i

        v_now = v_next; //sets voltage value to the next value
    }
    std::cout << "\nConstant Current Simulation Complete\n" << std::endl;  //print notice of current sim completion
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void runConstVoltage(double dt, int num_steps, double r, double v_source, Capacitor &volts)  //function for constant voltage simulation (RC) Simulation
{
    double i_now = v_source / r;  //current at t=0 is v_source/r
    double v_now = 0.0;  //voltage variable at t=0 is initiated to 0V
    volts.time[0] =  0.0; //assigning initial t=0
    volts.voltage[0] = v_now;  //assigning initial voltage to v_now
    volts.current[0] = i_now;  //assigning initial current to i_now    

    for (int j = 1; j < num_steps + 1; j++)  //loop for number of timesteps
    {    
        double i_next = i_now - (i_now / (r * volts.C)) * dt;  //subtracts previous current from next current
        double v_next = v_now + (i_now * dt * (1.0 / volts.C));  //adds previous voltage to next voltage

        volts.time[j] = dt * j;  //assigning time index j to dt * j
        volts.voltage[j] = v_next;  //assigning voltage index j to present value v_next
        volts.current[j] = i_next;  //assigning current index j to present value i_next

        i_now = i_next;  //sets current value to the next value
        v_now = v_next;  //sets voltage value to the next value
    }
    std::cout << "Constant Voltage Simulation Complete\n" << std::endl;  //print notice of voltage sim completion
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void printResultsAndClearMemory(Capacitor &amps, Capacitor &volts, int num_steps)  //function to print simulation results and clear allocated memory
{
    for (int j = 0; j < num_steps + 1; j = j + 200)  //loop for number of timesteps + 1 for t=0
    {
        std::cout << "\nFor Current Source Circuit, Time = " << amps.time[j] 
        << ", Current = " << amps.current[j] << ", Voltage = " << amps.voltage[j];  //prints current source time, current and voltage values 
    }
    std::cout << "\n" << std::endl;

    for (int j = 0; j < num_steps + 1; j = j + 200)  //loop for number of timesteps + 1 for t=0
    {
        std::cout << "\nFor Voltage Source Circuit, Time = " << volts.time[j] 
        << ", Current = " << volts.current[j] << ", Voltage = " << volts.voltage[j];  //prints voltage source time, current and voltage values  
    }    
    std::cout << "\n\nPrint out Complete" << std::endl;  //indication of value printout completion
    
    delete[] amps.time;  //section completes deletion of amps.time struct memory allocation
    delete[] amps.voltage;  //section completes deletion of amps.voltage struct memory allocation
    delete[] amps.current;  //section completes deletion of amps.current struct memory allocation

    delete[] volts.time;  //section completes deletion of volts.time struct memory allocation
    delete[] volts.voltage;  //section completes deletion of volts.voltage struct memory allocation
    delete[] volts.current;  //section completes deletion of volts.current struct memory allocation

    std::cout << "\nMemory Allocation Deletion Complete\n" << std::endl;  //indication of successful memory allocation deletion
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main()  //main function
{
    double d_t = 1e-10;  //delta time constant in seconds
    double final_t = 5e-6;  //final time constant in seconds
    int num_steps = 50000;  //number of timesteps constant
    double r = 1000;  //1k ohm resistor constant
    double c = 100e-12;  //100pF capacitor constant
    double i_source = 1e-2;  //10mA current source constant
    double v_source = 10.0;  //10V voltage source constant

    Capacitor amps;  //creates struct to capture current simulation values
    amps.time = new double[num_steps + 1];  //time array memory allocation for num_steps + t=0
    amps.voltage = new double[num_steps + 1];  //time array memory allocation for num_steps + t=0
    amps.current = new double[num_steps + 1];  //current array memory allocation for num_steps + t=0
    amps.C = c;  //capacitance array memory allocation for num_steps + t=0

    Capacitor volts;  //creates struct to capture voltage simulation values
    volts.time = new double[num_steps + 1];  //time array memory allocation for num_steps + t=0
    volts.voltage = new double[num_steps + 1];  //time array memory allocation for num_steps + t=0
    volts.current = new double[num_steps + 1];  //current array memory allocation for num_steps + t=0
    volts.C = c;  //capacitance array memory allocation for num_steps + t=0

    runConstCurrent(d_t, num_steps, i_source, amps); //call constant current simulation
    runConstVoltage(d_t, num_steps, r, v_source, volts);  //call function for constant voltage simulation
    printResultsAndClearMemory(amps, volts, num_steps);  //call function to print simulation results and clear allocated memory

    return 0;  //return 0 to exit main()
}
