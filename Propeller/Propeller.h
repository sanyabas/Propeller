// Propeller.h
#include <cmath>
#pragma once

using namespace System;

namespace Propeller {
	public ref class Data
	{
	public:
		float NailX;
		float NailY;
		float PropellerX;
		float PropellerY;
		float Angle;

		Data(float nailX, float nailY, float propellerX, float propellerY, float angle)
		{
			NailX = nailX;
			NailY = nailY;
			PropellerX = propellerX;
			PropellerY = propellerY;
			Angle = angle;
		}
	};

	public ref class PropellerMath
	{
	public:
		static const int L = 10;
		static const double A = 10;
		static const double Om = 100;
		static const double h = 2E-3;
		static const double kappa = 0.5;
		static const double g0 = 9.8;
		static double g = 9.8;
		static bool contact = true;
		static double alpha = -1;
		static double alpha_new;
		static double omega = 0;
		static double omega_new;
		static double x,y,vx,vy,ax;
		static double beta = alpha;
		static double epsilon = -g*sin(alpha) / L - kappa*omega;
		static double epsilon_new;
		static double ay = -omega*omega*L*cos(alpha);
		
		static Propeller::Data ^ GetCurrentValues(Propeller::Data ^ previous, int n);
	};

	
}
