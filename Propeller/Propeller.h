// Propeller.h
#include <cmath>
#include <stdio.h>
#pragma once

using namespace System;

#define Pi      3.141592653589793238462643

namespace Propeller {
	public ref class Data
	{
		//Структура с координатами и углом поворота
	public:
		float NailX;
		float NailY;
		float PropellerX;
		float PropellerY;
		float Angle;
		float Gx;
		float Gy;
		

		Data(float nailX, float nailY, float propellerX, float propellerY, float angle, float gx,float gy)
		{
			NailX = nailX;
			NailY = nailY;
			PropellerX = propellerX;
			PropellerY = propellerY;
			Angle = angle;
			Gx = gx;
			Gy = gy;
		}
	};

	public ref class PropellerMath
	{
		//Константы и текущие значения величин в СИ
	public:
		static const float R = 0.0015; //радиус отверстия
		static const float L_eff = (0.01*0.01 + 0.03*0.03) / (12 * R);
		static const double A = 0.005;
		static const double Om = 2 * Pi * 15;
		static const double h = 0.0002;
		static const double kappa = 0.2;
		static const double g0 = 9.8;
		static double g = 9.8;
		static bool contact = true;
		static double alpha = 0.1; //угол поворота
		static double alpha_new;
		static double omega = 0;
		static double omega_new;
		static double x,y,vx,vy,ax;
		static double beta = alpha;
		static double epsilon = -g*sin(alpha) / L_eff - kappa*omega;
		static double epsilon_new;
		static double ay = -omega*omega*R*cos(alpha);
		static FILE* fout = fopen("report_75", "wt");
		static double gx;
		static double gy;
		
		static Propeller::Data ^ GetCurrentValues(Propeller::Data ^ previous, int n);
	};

	
}
