#include "ParametricSpline.h"



int main()
{

	ParametricSpline parametricSpline = ParametricSpline();

	const int VALUE_COUNT = 3;
	double* x = new double[VALUE_COUNT]{ 0, 1, 2 };
	double* y = new double[VALUE_COUNT]{ 0, 3, 0 };
	double* z = new double[VALUE_COUNT]{ 1, 2, 3 };

	parametricSpline.Compute(x, y, z, VALUE_COUNT);

	const int STEPS = 10;
	for (int i = 0; i < parametricSpline.GetSegmentCount(); i++)
	{
		
		for (int j = 0; j < STEPS; j++)
		{
			double t = i + (double)j / (STEPS);
			double* position = parametricSpline.eval(t);
			printf("new Vector3(%ff, %ff, %ff),\n", position[0], position[1], position[2]);
		}
	}

	return 0;
}