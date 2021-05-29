#ifndef _B_SYSTEM_H_
#define _B_SYSTEM_H_

#include <iostream>
#include <vector>

using namespace std;

#include "Ode.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>


class B_system{
	public:
		B_system(double ini_vx_pass, double ini_vy_pass,
				 double ini_xx_pass, double ini_xy_pass,
				 double t_start_pass, double t_end_pass);
		~B_system();
		void solve();                  //solve the ODE and do the interpolation
		double vx(double t_now);       //return velocity in x direction at t_now
		double vy(double t_now);       //return velocity in y direction at t_now
		double xx(double t_now);       //return location in x direction at t_now
		double xy(double t_now);       //return location in y direction at t_now

	private:
		double ini_vx;                 //initial velocity in x direction
		double ini_vy;                 //initial velocity in x direction
		double ini_xx;                 //initial location in x direction
		double ini_xy;                 //initial location in x direction
		double t_start;                //the start time
		double t_end;                  //the end time
		int N = 1000;      			   //number of dots used in solving ODE
		ODE ode;                       //the initinization of the ODE class see the B_system constructor
		vector<double> ti_ode;         //this vector stores all
		vector<double> vx_ode;         //this vector stores all velocity in x dirction solved from ODE
		vector<double> vy_ode;         //this vector stores all velocity in y dirction solved from ODE
		gsl_interp_accel *vx_acc;      //workspace for interpolation loop up
		gsl_interp_accel *vy_acc;      //workspace for interpolation loop up
		gsl_spline *vx_spline;         //workspace for interpolation interface
		gsl_spline *vy_spline;         //workspace for interpolation interface
};

#endif
