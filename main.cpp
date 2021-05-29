//  Compile command: g++ main.cpp Ode.cpp B_system.cpp -o main.x -O2 -std=c++17 -lgsl -lgslcblas
//
//    A program to calculate the trajectory of an electron in a varying magnetic field. It uses GSL library to solve the ODEs
//  for the velocity of the electron, interpolate the velocity and integrate the velocity to get the placement of the
//  electron. The magnetic field is defined in ODE.cpp

#include <iostream>
#include <fstream>
#include <cmath>
#include "B_system.h"

using namespace std;

int main(){
	ofstream fout("output.dat");             //create a file output stream
	fout << "# t vx vy xx xy" << endl;       //header of the output file

	double t_start = 0.0, t_end = 24.0;      //the start and end time
	double t_gap = 0.05;                     //the time gap in the plot
	int N_ = (t_end - t_start)/t_gap;        //the number of dots in the plot
	double ini_vx = 1.0;                     //the initial velocity in x direction
	double ini_vy = 0.0;                     //the initial velocity in y direction
	double ini_xx = 1.0;                     //the initial location in x direction
	double ini_xy = 0.0;                     //the initial location in y direction
	B_system system(ini_vx, ini_vy, ini_xx, ini_xy, t_start, t_end);
	system.solve();                          //solve the system using provided parameters


	for (int i = 0; i <= N_; i++) {
		double ti_ = t_start + i * t_gap;    //the current time
		double vxi_ = system.vx(ti_);        //the current velocity in x direction
		double vyi_ = system.vy(ti_);        //the current velocity in y direction
		double xxi_ = system.xx(ti_);        //the current location in x direction
		double xyi_ = system.xy(ti_);        //the current location in y direction
		fout << ti_ << " " << vxi_ << " " << vyi_ << " " << xxi_ << " " << xyi_ << endl;
	}
	fout.close();							 //close file output stream
	return 0;
}
