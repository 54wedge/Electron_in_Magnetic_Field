#ifndef _ODE_H_
#define _ODE_H_

#include <iostream>
#include <cmath>
using namespace std;

#include "gsl/gsl_errno.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_odeiv2.h"

class ODE{
    public:
        ODE(double y0_pass, double y1_pass);
        ~ODE();
        void solve(double ti);           //solve the ode at time ti
        double y0();                     //return the solved velcoty in x direction at ti
        double y1();                     //return the solved velcoty in y direction at ti

    private:
        double t = 0;                    //time initilized with value 0 to avoid error
        double y[2];                     //array of the solution of ode
        gsl_odeiv2_system sys;           //ode system
        gsl_odeiv2_driver *driver;       //ode driver
        static int function(double t, const double y[], double f[], void *params);
        static int jacobian(double t, const double y[], double *dfdy, double dfdt[], void *params);
};

double B_field(double t);                //magetic field expression

#endif
