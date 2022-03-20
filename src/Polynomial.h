#pragma once

class Polynomial
{
	double cubic_;
	double squared_;
	double linear_;
	double constant_;

public:
	Polynomial(double cubic, double squared, double linear, double constant)
		: cubic_(cubic), squared_(squared), linear_(linear), constant_(constant)
	{
	}

	double GetCubic()
	{
		return cubic_;
	}

	double GetSquared()
	{
		return squared_;
	}

	double GetLinear()
	{
		return linear_;
	}

	double GetConstant()
	{
		return constant_;
	}
};