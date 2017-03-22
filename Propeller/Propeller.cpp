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
		/*Data^ result = gcnew Data();*/
	/*	double x;
		double y;
		double vx;
		double vy;*/
		
		double y_gvozd = -A*sin(Om*n*h);
		double a_gvozd = A*Om*Om*sin(Om*n*h);
		/*double epsilon;
		double epsilon_new;*/
		g = g0 - a_gvozd;
		
		if (contact)
		{
			x = L*sin(alpha);
			y = L*cos(alpha);
			vx = omega*L*cos(alpha);
			vy = -omega*L*sin(alpha);
			ax = -omega*omega*L*sin(alpha);
			ay = -omega*omega*L*cos(alpha);
			alpha_new = alpha + h*omega + 0.5*h*h*epsilon;
			beta += h*omega + 0.5*h*h*epsilon;
			double omega_tmp = omega + h*epsilon;
			epsilon_new = -g*sin(alpha_new) / L - kappa*omega_tmp;
			omega_new = omega + 0.5*h*(epsilon + epsilon_new);
			if (ay*g > 0 && ay*g < g*g)
				contact = 0;
		}
		else
		{
			x += vx*h;
			y += vy*h + 0.5*h*h*g;
			vy += h*g;
			beta += omega*h;
			if (x*x + y*y >= L*L)
			{
				contact = 1;
				alpha_new = atan(x / y);
			}
		}

		alpha = alpha_new;
		omega = omega_new;
		epsilon = epsilon_new;

		double x_LS = x;            //  координаты центра отверстия  
		double y_LS = y_gvozd + y;  //  в лабораторной СО
		return gcnew Data(0,y_gvozd,x_LS,y_LS,beta);
	}
//}
