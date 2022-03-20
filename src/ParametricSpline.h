#pragma once
#include "CubicSpline.h"

class ParametricSpline
{
    //Spline responsible for the x-coordinate 
    CubicSpline splineX_;

    //Spline responsible for the y-coordinate 
    CubicSpline splineY_;

    //Spline responsible for the z-coordinate 
    CubicSpline splineZ_;


public:
    ParametricSpline()
    {

    }

    int GetSegmentCount()
    {
        int segmentCountX = splineX_.GetSegmentCount();
        int segmentCountY = splineY_.GetSegmentCount();
        int segmentCountZ = splineZ_.GetSegmentCount();

        //check if all 3 values are equal
        if (segmentCountX == segmentCountY && segmentCountY == segmentCountZ)
        {
            return segmentCountX;
        }
        else
        {
            printf("Error: SegmentCounts are nnot equal\n");
            return 0;
        }
    }

    void Compute(double* x, double* y, double* z, int valueCount)
    {
        splineX_ = CubicSpline();
        splineY_ = CubicSpline();
        splineZ_ = CubicSpline();

        //every spline is responsible for the one dimension of the parametric spline
        splineX_.Compute(x, valueCount);
        splineY_.Compute(y, valueCount);
        splineZ_.Compute(z, valueCount);
    }

    double* eval(float t)
    {
        return new double[] {splineX_.eval(t), splineY_.eval(t), splineZ_.eval(t)};
    }

};