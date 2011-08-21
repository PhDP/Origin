#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "seshat.h"
#include "maths.h"

double hypot(double a, double b)
{
	if (fabs(a) > fabs(b))
	{
		const double r = b / a;
		return fabs(a) * sqrt(1 + r * r);
	}
	else if (b != 0.0)
	{
		const double r = a / b;
		return fabs(b) * sqrt(1 + r * r);
	}
	else
	{
		return 0.0;
	}
}
