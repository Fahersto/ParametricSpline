#pragma once

#include "Polynom.h"

#include <vector>

/*
* Implemenation of a cubic spline based on the algorithm "Natural Cubic Spline" described in "Numerical Analysis" by Richard L. Burden and J. Douglas Faires
*/
class CubicSpline
{

    std::vector<Polynom> polynoms_;

public:
    ~CubicSpline()
    {

    }

    /**
    * Returns the number of segments/polynoms
    */
    int GetSegmentCount()
    {
        return polynoms_.size();
    }

    /**
    * Evaluate  the CubicSpline
    */
    double eval(double t)
    {
        //Rounding downm t gives the number of the segment. This works because t is chosen to be: segment1[0,1], segment2[1,2]..
        int segmentNumber = (int)t;

        if (segmentNumber >= polynoms_.size())
        {
            printf("Error: t value is exceeds segments\n");
            return 0;
        }
        //map each segment form [0, 1]
        double normalizedT = t - segmentNumber;
        Polynom polynom = polynoms_[segmentNumber];

        return  polynom.GetCubic() * normalizedT * normalizedT * normalizedT +
            polynom.GetSquared() * normalizedT * normalizedT +
            polynom.GetLinear() * normalizedT +
            polynom.GetConstant();
    }


    /**
    * Computes the 1D-Spline based on the values given. The parametric value t goes from segment1: [0, 1], segment2:[1,2], ...,  segmentN:[N-1,N]
    * By using multiple Splines it is possible to describe positions in 2D, 3D ...
    */
    void Compute(double* values, int valueCount)
    {
        //this should not be necessary
        double* x = new double[valueCount];
        double* a = new double[valueCount];
        for (int i = 0; i < valueCount; i++)
        {
            x[i] = i; // this makes segment t vals: [0,1], [1,2] ... This is asumed when finding the corresponding segment to a t value.
            a[i] = values[i];
        }

        if (valueCount == 0)
        {
            //Debug.LogError("Trying to compute spline without points");
            printf("Error: Trying to compute spline without points\n");
            return;
        }

        //number of segments is equal to number of points - 1
        int segmentCount = valueCount - 1;
   

        //Implementation of the books algorithm
        //allocate memory
        double* b = new double[segmentCount + 1];
        double* c = new double[segmentCount + 1];
        double* d = new double[segmentCount + 1];

        //step 1
        double* h = new double[segmentCount];
        for (int i = 0; i <= segmentCount - 1; i++)
        {
            h[i] = x[i + 1] - x[i];
        }

        //step 2
        double* alpha = new double[segmentCount];
        for (int i = 1; i <= segmentCount - 1; i++)
        {
            alpha[i] = (3 / h[i]) * (a[i + 1] - a[i]) - (3 / h[i - 1]) * (a[i] - a[i - 1]);
        }

        //step 3
        //step 3,4,5 and part of 6 solve tridiagonal system
        double* l = new double[segmentCount + 1];
        double* u = new double[segmentCount + 1];
        double* z = new double[segmentCount + 1];
        l[0] = 1;
        u[0] = 0;
        z[0] = 0;

        //step 4
        for (int i = 1; i <= segmentCount - 1; i++)
        {
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
            u[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
        }

        delete[] x;
        delete[] alpha;

        //step 5
        l[segmentCount] = 1;
        z[segmentCount] = 0;
        c[segmentCount] = 0;

        delete[] l;

        //step 6
        for (int j = segmentCount - 1; j >= 0; j--)
        {
            c[j] = z[j] - u[j] * c[j + 1];
            b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
            d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
        }

        delete[] h;
        delete[] u;
        delete[] z;

        for (int i = 0; i < segmentCount; i++)
        {
            polynoms_.push_back(Polynom(d[i], c[i], b[i], a[i]));
        }

        delete[] a;
        delete[] b;
        delete[] c;
        delete[] d;
    }
};