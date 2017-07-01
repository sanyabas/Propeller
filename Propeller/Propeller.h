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
		float PropellerOmega;
		float Angle;
		float Gx;
		float Gy;
		

		Data(float nailX, float nailY, float propellerX, float propellerY, float propellerOm, float angle, float gx,float gy)
		{
			NailX = nailX;
			NailY = nailY;
			PropellerX = propellerX;
			PropellerY = propellerY;
			Angle = angle;
			Gx = gx;
			Gy = gy;
			PropellerOmega = propellerOm;
		}
	};

	public ref class PropellerConsts
	{
	public:
		float NailAmplitude;
		float NailOmega;

		PropellerConsts(float nailAmp,float nailOm)
		{
			NailAmplitude = nailAmp;
			NailOmega = nailOm;
		}
	};

	public ref class PropellerMath
	{
		//Константы и текущие значения величин в СИ
	public:
		static const float a = 0.01; // сторона прямоугольного пропеллера
		static const float b = 0.03; // сторона прямоугольного пропеллера
		static const float R = 0.003; //радиус отверстия
		static const float r = 0.002; //радиус гвоздика
									  //static const float L_eff = (0.01*0.01 + 0.03*0.03) / (12 * R);
		static const double znamen = R*(1 + (a*a + b*b) / (12 * R*R));

		static const double A = 0.01;
		static const double Om = 2 * Pi * 0.25;
		static const double phi2 = 0.5 * Pi; // фаза у-колебаний гвоздика
		static const double h = 0.003;
		static const double kappa = 0.5;
		static const double g0 = 0.1;
		static double gx, gx_new;
		static double gy, gy_new;
		static double g_eff = sqrt(gx*gx + gy*gy), g_eff_new;
		static bool contact = true;
		static double alpha = 0.; //угол поворота
		static double alpha_new;
		static double omega = 0;
		static double omega_new;
		static double x, y,/*vx,vy,*/ ax;
		static double beta = alpha, beta_new;
		static double epsilon = 0.;
		static double epsilon_new;
		static double ay = -omega*omega*R*cos(alpha);
		static FILE* fout = fopen("report_75", "wt");
		
		static Propeller::Data ^ GetCurrentValues(Propeller::Data ^ previous, int n);
		static PropellerConsts ^ GetConsts();
	};

	
}
