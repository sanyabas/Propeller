#include "stdafx.h"
#include <stdio.h>
#include <math.h>

int main()
{
	long int n;

	double alpha, alpha_new; // ���� ����� ���������� � ����� �������-����� ���������
	double omega, omega_new; // ������� �������� �������� ������ ��������� ������ ��������
	double epsilon, epsilon_new; // ������� ��������� ������ ��������� ������ ��������

	double L = 0.1;  // ������ ��������� (�������� �������)
	double A = 0.35;  // ��������� ��������� �������� (�������� �������)
	double Om = 10.; // ������� (�����������) ������������ ��������� �������� (�������� �������)

	double h = 0.001; // ��� �� �������
	double kappa = 0.5; // ����� ���� ������

	double x, y, vx, vy, ax, ay; // ����������, ��������, ��������� ������ ��������� � ������� �������, ��������� � ���������
	double a_gvozd; // ��������� �������� � ������������ ������� �������

	FILE* fout = fopen("report", "wt");

	// ��� Oy ��������� ����!
	double g = 9.8;  // ��������� ���������� ������� (� �����. ��)

	alpha = 0.1;  // ��������� ���� ���������� ������ ������
	omega = 0;

	double beta = alpha; // ���� ����� ���������� � ���� ����������

	epsilon = -g*sin(alpha) / L - kappa*omega;
	ay = -omega*omega*L*cos(alpha);

	int contact = 1;  // ���� �� ������� ����� ��������� � ����������
	for (n = 1; n<500000; n++)
	{
		double y_gvozd = -A*sin(Om*n*h);   // ���������� �������� � ������������ ��
										   //v_gvozd = -A*Om*cos(Om*n*h);
		a_gvozd = A*Om*Om*sin(Om*n*h); // � ������������ ������� �������
		g = 9.8 - a_gvozd;   // � ������� ������� ��������

							 //if () contact = 1; // ����� ���������
							 //if (ay*g>0 && ay*g<g*g) contact = 0;
							 //else             contact = 1;
		if (contact)
		{

			x = L*sin(alpha);
			y = L*cos(alpha); // ��������� ������ ��������� � �� ��������
			vx = omega*L*cos(alpha);
			vy = -omega*L*sin(alpha);

			ax = -omega*omega*L*sin(alpha);  // ������������������� ��������� 
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

		double x_LS = x;            //  ���������� ������ ���������  
		double y_LS = y_gvozd + y;  //  � ������������ ��

		fprintf(fout, "%d %g %g %g %g %g %g %g %.10g\n", contact, n*h, alpha_new, beta, omega_new, epsilon_new, ay, g, y_LS);

		//     ��� �������� �����:
		//	   ���������� �������� (0, y_gvozd),
		//     ���������� ������ ��������� (x_LS, y_LS),
		//     ���� beta ����� ���������� � ���������� ���� ���������� (�� � ��������).
		//     ��� Oy � ���� ���������� ����, ��� Ox, ��� ������, ������.

	}
	fclose(fout);
	return 0;
}
