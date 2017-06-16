#include "stdafx.h"
#include <stdio.h>
#include <math.h>

int main()
{
	long int n;

	double alpha, alpha_new; // угол между вертикалью и лучом гвоздик-центр отверстия
	double omega, omega_new; // угловая скорость вращения центра отверстия вокруг гвоздика
	double epsilon, epsilon_new; // угловое ускорение центра отверстия вокруг гвоздика

	double L = 0.1;  // радиус отверстия (задается исходно)
	double A = 0.35;  // амплитуда колебаний гвоздика (задается исходно)
	double Om = 10.; // частота (циклическая) вертикальных колебаний гвоздика (задается исходно)

	double h = 0.001; // шаг по времени
	double kappa = 0.5; // нечто типа трения

	double x, y, vx, vy, ax, ay; // координаты, скорость, ускорение центра отверстия в системе отсчета, связанной с гвоздиком
	double a_gvozd; // ускорение гвоздика в лабораторной системе отсчета

	FILE* fout = fopen("report", "wt");

	// ось Oy направляю вниз!
	double g = 9.8;  // ускорение свободного падения (в лабор. СО)

	alpha = 0.1;  // начальный угол отклонения центра обруча
	omega = 0;

	double beta = alpha; // угол между вертикалью и осью пропеллера

	epsilon = -g*sin(alpha) / L - kappa*omega;
	ay = -omega*omega*L*cos(alpha);

	int contact = 1;  // есть ли контакт между гвоздиком и отверстием
	for (n = 1; n<500000; n++)
	{
		double y_gvozd = -A*sin(Om*n*h);   // координата гвоздика в лабораторной СО
										   //v_gvozd = -A*Om*cos(Om*n*h);
		a_gvozd = A*Om*Om*sin(Om*n*h); // в лабораторной системе отсчета
		g = 9.8 - a_gvozd;   // в системе отсчета гвоздика

							 //if () contact = 1; // вроде правильно
							 //if (ay*g>0 && ay*g<g*g) contact = 0;
							 //else             contact = 1;
		if (contact)
		{

			x = L*sin(alpha);
			y = L*cos(alpha); // коодинаты центра отверстия в СО гвоздика
			vx = omega*L*cos(alpha);
			vy = -omega*L*sin(alpha);

			ax = -omega*omega*L*sin(alpha);  // центростремительное ускорение 
			ay = -omega*omega*L*cos(alpha);

			alpha_new = alpha + h*omega + 0.5*h*h*epsilon;
			beta += h*omega + 0.5*h*h*epsilon;
			double omega_tmp = omega + h*epsilon;
			epsilon_new = -g*sin(alpha_new) / L - kappa*omega_tmp;
			omega_new = omega + 0.5*h*(epsilon + epsilon_new);
			if (ay*g>0 && ay*g<g*g) contact = 0;
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

		fprintf(fout, "%d %g %g %g %g %g %g %g %.10g\n", contact, n*h, alpha_new, beta, omega_new, epsilon_new, ay, g, y_LS);

		//     для картинки нужны:
		//	   координаты гвоздика (0, y_gvozd),
		//     координаты центра отверстия (x_LS, y_LS),
		//     угол beta между вертикалью и продольной осью пропеллера (он в радианах).
		//     Ось Oy у меня направлена ВНИЗ, ось Ox, как обычно, вправо.

	}
	fclose(fout);
	return 0;
}
