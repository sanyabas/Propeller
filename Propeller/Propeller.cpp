// This is the main DLL file.

#include "stdafx.h"

#include "Propeller.h"
namespace Propeller
{
	//using namespace Propeller;
	Data ^ PropellerMath::GetCurrentValues(Data ^ previous, int n)
	{
		//Алгоритм пересчёта угла и положения пропеллера
		double x_gvozd = A*sin(Om*n*h);
		double y_gvozd = A*cos(Om*n*h);
		double ax_gvozd = -A*Om*Om*sin(Om*n*h), ax_gvozd_new;
		double ay_gvozd = -A*Om*Om*cos(Om*n*h), ay_gvozd_new;
		gx = -ax_gvozd;
		gy = g0 - ay_gvozd;
		g_eff = sqrt(gx*gx + gy*gy);
		if (gy >= 0) beta = atan(gx / gy);
		else       beta = atan(gx / gy) + Pi;

		ax_gvozd_new = -A*Om*Om*sin(Om*h*(n + 1)); // в лабораторной системе отсчета
		ay_gvozd_new = -A*Om*Om*cos(Om*h*(n + 1)); // в лабораторной системе отсчета
		gx_new = -ax_gvozd_new;   // в системе отсчета гвоздика; уже новое
		gy_new = g0 - ay_gvozd_new;   // в системе отсчета гвоздика; уже новое
		g_eff_new = sqrt(gx_new*gx_new + gy_new*gy_new);
		if (gy_new >= 0) beta_new = atan(gx_new / gy_new);
		else           beta_new = atan(gx_new / gy_new) + Pi;

		while (beta_new < beta - 5)
		{
			beta_new += 2 * Pi;
		}
		while (beta_new > beta + 5)
		{
			beta_new -= 2 * Pi;
		}

		double Om_g_eff = (beta_new - beta) / h;


		if (contact)
		{
			alpha_new = alpha + h*omega + 0.5*h*h*epsilon;
			double omega_tmp = omega + h*epsilon;
			epsilon_new = -g_eff_new*sin(alpha_new - beta_new) / znamen - kappa*(omega_tmp - Om);
			//epsilon_new = -g_eff*sin(alpha_new) / L_eff - kappa*omega_tmp;
			omega_new = omega + 0.5*h*(epsilon + epsilon_new);

			x = (R - r)*sin(alpha_new);
			y = (R - r)*cos(alpha_new); // координаты центра масс пропеллера
										//vx = omega*R*cos(alpha_new);
										//vy = -omega*R*sin(alpha_new);
			ax = -omega*omega*(R - r)*sin(alpha_new);  // центростремительное
			ay = -omega*omega*(R - r)*cos(alpha_new);

			beta += h*omega + 0.5*h*h*epsilon;

		}

		alpha = alpha_new;
		omega = omega_new;
		epsilon = epsilon_new;

		ax_gvozd = ax_gvozd_new; // в лабораторной системе отсчета
		ay_gvozd = ay_gvozd_new; // в лабораторной системе отсчета
		gx = gx_new;   // в системе отсчета гвоздика;
		gy = gy_new;   // в системе отсчета гвоздика;
		g_eff = g_eff_new;
		beta = beta_new;

		double x_LS = x_gvozd + x;            //  координаты центра отверстия  
		double y_LS = y_gvozd + y;  //  в лабораторной СО
		fprintf(fout, "%g %g %g %g %g %g %g %.10g\n", n*h, alpha_new, beta, omega, epsilon_new, ay, g_eff, x_LS);
		return gcnew Data(x_gvozd, y_gvozd, x_LS, y_LS, omega_new,(1 - r / R)*alpha,gx,gy);
	}

	PropellerConsts ^ PropellerMath::GetConsts()
	{
		return gcnew PropellerConsts(A, Om);
	}
}
//}
