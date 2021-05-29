#include "B_system.h"

B_system::B_system(double ini_vx_pass, double ini_vy_pass,    //constructor
				   double ini_xx_pass, double ini_xy_pass,
				   double t_start_pass, double t_end_pass)
				   :ode(ini_vx_pass, ini_vy_pass){            //object ode's initialization here
	ini_vx = ini_vx_pass;
	ini_vy = ini_vy_pass;
	ini_xx = ini_xx_pass;
	ini_xy = ini_xy_pass;
	t_start = t_start_pass;
	t_end = t_end_pass;
	vx_acc = gsl_interp_accel_alloc ();     //alloc workspace for interpolation
	vy_acc = gsl_interp_accel_alloc ();     //alloc workspace for interpolation
}

B_system::~B_system(){                      //destructor
	gsl_spline_free (vx_spline);
	gsl_spline_free (vy_spline);
    gsl_interp_accel_free (vx_acc);
    gsl_interp_accel_free (vy_acc);
}

void B_system::solve(){                      //solve the ODE and do the interpolation
	for (int i = 0; i <= N; i++) {
		double ti = t_start + i*((t_end - t_start)/N);
		ode.solve(ti);                       //solve the ODE at time ti
		ti_ode.push_back(ti);
		vx_ode.push_back(ode.y0());          //ode.y0() returns the velcoty in x direction at ti
		vy_ode.push_back(ode.y1());          //ode.y1() returns the velcoty in y direction at ti
	}
	vx_spline = gsl_spline_alloc (gsl_interp_cspline, vx_ode.size());  //interpolation workspace
    vy_spline = gsl_spline_alloc (gsl_interp_cspline, vy_ode.size());  //interpolation workspace
	gsl_spline_init(vx_spline, ti_ode.data(), vx_ode.data(), vx_ode.size());     //interpolation
	gsl_spline_init(vy_spline, ti_ode.data(), vy_ode.data(), vy_ode.size());     //interpolation
}

double B_system::vx(double t_now){           //return vx(t_now) after interpolation
	return gsl_spline_eval(vx_spline, t_now, vx_acc);
}

double B_system::vy(double t_now){           //return vy(t_now) after interpolation
	return gsl_spline_eval(vy_spline, t_now, vy_acc);
}

double B_system::xx(double t_now){           //return xx(t_now) after interpolation
	return ini_xx + gsl_spline_eval_integ(vx_spline, t_start, t_now, vx_acc);
}

double B_system::xy(double t_now){           //return xy(t_now) after interpolation
	return ini_xy + gsl_spline_eval_integ(vy_spline, t_start, t_now, vy_acc);
}
