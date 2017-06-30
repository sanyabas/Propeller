// This is the main DLL file.

#include "stdafx.h"

#include "Propeller.h"
//namespace Propeller
//{
	//static Data GetCurrentValues(Data)
	//{
	//	double y_gvozd = -A*sin(Om*n*h);
	//}
	Propeller::Data ^ Propeller::PropellerMath::GetCurrentValues(Propeller::Data ^ previous, int n)
	{
		//Алгоритм пересчёта угла и положения пропеллера
		double y_gvozd = -A*sin(Om*n*h);
		double a_gvozd = A*Om*Om*sin(Om*n*h);
		g = g0 - a_gvozd;
		double g_old = 9.8 - A*Om*Om*sin(Om*(n - 1)*h);   // в системе отсчета гвоздика; —“ј–ќ≈
		
		if (contact)
		{
			alpha_new = alpha + h*omega + 0.5*h*h*epsilon;
			double omega_tmp = omega + h*epsilon;
			epsilon_new = -g*sin(alpha_new) / L_eff - kappa*omega_tmp;
			omega_new = omega + 0.5*h*(epsilon + epsilon_new);

			x = R*sin(alpha_new);
			y = R*cos(alpha_new); // координаты центра масс пропеллера
			vx = omega*R*cos(alpha_new);
			vy = -omega*R*sin(alpha_new);
			ax = -omega*omega*R*sin(alpha_new);  // центростремительное
			ay = -omega*omega*R*cos(alpha_new);

			beta += h*omega + 0.5*h*h*epsilon;
			
			if (ay*g > 0 && ay*g < g*g)
				contact = 0;
		}
		else
		{
			x += vx*h;
			y += vy*h + 0.5*h*h*g_old;
			vy += h*0.5*(g_old + g);
						
			beta += omega*h;
			if (x*x + y*y >= R*R)
			{
				contact = 1;
				if (y >= 0) alpha_new = atan(x / y);    // NEW 
				else      alpha_new = atan(x / y) + Pi;   // NEW	 
				//alpha_new = atan(x / y);
				double ex = sin(alpha_new);
				double ey = cos(alpha_new);

				double v_perp_x = vx - ex*(vx*ex + vy*ey);
				double v_perp_y = vy - ey*(vx*ex + vy*ey);

				double omega_udar = sqrt(v_perp_x*v_perp_x + v_perp_y*v_perp_y) / R;

				if (ex*v_perp_y - ey*v_perp_x > 0)  omega_udar *= -1;

				omega_new = omega_new + omega_udar;			
			}
		}

		alpha = alpha_new;
		omega = omega_new;
		epsilon = epsilon_new;

		double x_LS = x;            //  координаты центра отверстия  
		double y_LS = y_gvozd + y;  //  в лабораторной СО
		gx = cos(n);
		gy = sin(n);
		fprintf(fout, "%d %g %g %g %g %g %g %g %.10g\n", contact, n*h, alpha_new, beta, omega, epsilon_new, ay, g, x_LS);
		return gcnew Data(0,y_gvozd,x_LS,y_LS,alpha,gx,gy);
	}

Propeller::PropellerConsts ^ Propeller::PropellerMath::GetConsts()
	{
	return gcnew PropellerConsts(A, Om);
	}
//}
