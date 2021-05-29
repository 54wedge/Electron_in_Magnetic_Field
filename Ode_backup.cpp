#include "Ode.h"

ODE::ODE(double y0_pass, double y1_pass){   //constructor
    sys.function = function;
    sys.jacobian = jacobian;
    sys.dimension = 2;
    sys.params = NULL;
    driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk1imp, 1e-7, 1e-7, 0.0);
    y[0] = y0_pass;
    y[1] = y1_pass;
}

ODE::~ODE(){                                  //destuctor
    gsl_odeiv2_driver_free(driver);
}

void ODE::solve(double ti){         //solve the ode at ti
    gsl_odeiv2_driver_apply(driver, &t, ti, y);
}

double ODE::y0(){                         //return vx(ti)
    return y[0];
}

double ODE::y1(){                         //return vy(ti)
    return y[1];
}

int ODE::function(double t, const double y[], double f[], void *params){
    (void)(params);                   //unused parameters
    f[0] = B_field(t)* y[1];                //vx' =  w*vy
    f[1] = -B_field(t)* y[0];               //vy' = -w*vx
    return GSL_SUCCESS;
}

int ODE::jacobian(double t, const double y[], double *dfdy, double dfdt[], void *params){
    (void)(dfdt);                     //unused parameters
    (void)(y);                        //unused parameters
    (void)(params);                   //unused parameters
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
    gsl_matrix * m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);          //d(vx')/d(vx)
    gsl_matrix_set(m, 0, 1, B_field(t));   //d(vx')/d(vy)
    gsl_matrix_set(m, 1, 0, -B_field(t));  //d(vy')/d(vx)
    gsl_matrix_set(m, 1, 1, 0.0);          //d(vy')/d(vy)
    return GSL_SUCCESS;
}

//For debug
/*int main(void) {
    double t_start = 0.0, t_end = 24.0;
    int N = 100;
    ODE system(1.0, 0.0);
    for (int i = 0; i <= N; i++) {
        double ti = t_start + i * (t_end / N);
        system.solve(ti);
        cout << ti << " " << system.y0() << " " << system.y1() << endl;
    }
    return 0;
}*/

//{Put B_field below}
double B_field(double t){
	return cos(2*t)+3;
}
