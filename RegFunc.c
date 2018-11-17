//Regression Functions
#include <stdio.h>
#include <math.h>
#include "RegFunc.h"
#include "Matrix&Vector.h"

//Can be used in cpp!
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


int main()//testing
{
	double xarr[10] = {1.01, 2.01, 3.02, 4.1, 5.05, 6.06, 7.2, 8.15, 9.07, 10};
	double yarr[10] = {100.2, 50.9, 32.23, 27.75, 20, 17.34, 14.3, 12.34, 11.01, 10};
	double a, b, r;
	HypReg(xarr, yarr, 10, &a, &b, &r);
	printf("%lf\t%lf\t%lf\n", a, b, r);
	return 0;
}


//the average(mean) of a sequence
double Avg(double * arr, const unsigned int num)
{
	if (!(arr && num)) return 0;
	unsigned int i;	double sum;
	for (sum = i = 0; i < num; i++)
		sum = sum + arr[i];
	return sum / num;
}

//R^2 of a regression function
double RSqr(double * x, double * y, double * y_pred, const unsigned int num)
{
	if (!(x && y && y_pred && num)) return 0;
	unsigned int i;	double y_avg = Avg(y, num), SSReg, SSTot;
	for (SSReg = SSTot = i = 0; i < num; i++)
	{
		SSReg = SSReg + (y_pred[i] - y_avg) * (y_pred[i] - y_avg);
		SSTot = SSTot + (y[i] - y_avg) * (y[i] - y_avg);
	}
	if (SSTot != 0) return SSReg / SSTot;
	else return 0;
}


/*
Single Variable Liner Regression y=a+bx
params:
x and y: pointer of data array
num: number of data
a and b: output a and b
rsqr: output R^2 (optional, set 0 if not needed)
*/
void SVLinerReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr)
{
	if (!(x && y && num && a && b)) return;
	unsigned int i;	double sumx, sumy, sumxy, sumx2;
	for (sumx = sumy = sumxy = sumx2 = i = 0; i < num; i++)
	{
		sumx = sumx + x[i];
		sumy = sumy + y[i];
		sumxy = sumxy + x[i] * y[i];
		sumx2 = sumx2 + x[i] * x[i];
	}
	*b = (num * sumxy - sumx * sumy) / (num * sumx2 - sumx * sumx);
	*a = (sumy - (*b) * sumx) / num;
	if (rsqr) *rsqr = SVLinerReg_RSqr(x, y, num, *a, *b);
	return;
}

//R^2 of Single Variable Liner Regression
double SVLinerReg_RSqr(double * x, double * y, const unsigned int num, double a, double b)
{
	if (!(x && y && num)) return 0;
	unsigned int i;	double y_avg = Avg(y, num), SSReg, SSTot;
	for (SSReg = SSTot = i = 0; i < num; i++)
	{
		SSReg = SSReg + (a + b * x[i] - y_avg) * (a + b * x[i] - y_avg);
		SSTot = SSTot + (y[i] - y_avg) * (y[i] - y_avg);
	}
	if (SSTot != 0) return SSReg / SSTot;
	else return 0;
}


//Hyperbolic Regression y=1/(a+bx)
void HypReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr)
{
	if (!(x && y && num && a && b)) return;
	//convert to liner, z=1/y=a+bx
	double z[num];//temp
	for (unsigned int i = 0; i < num; i++)
		z[i] = 1.0 / y[i];
	//liner regression
	SVLinerReg(x, z, num, a, b, rsqr);
	//get R^2
	//if (rsqr) *rsqr = HypReg_RSqr(x, y, num, *a, *b);
	return;
}

//R^2 of hyp. reg.
double HypReg_RSqr(double * x, double * y, const unsigned int num, double a, double b)
{
	if (!(x && y && num)) return 0;
	unsigned int i;	double y_avg = Avg(y, num), SSReg, SSTot;
	for (SSReg = SSTot = i = 0; i < num; i++)
	{
		SSReg = SSReg + (1.0 / (a + b * x[i]) - y_avg) * (1.0 / (a + b * x[i]) - y_avg);
		SSTot = SSTot + (y[i] - y_avg) * (y[i] - y_avg);
	}
	if (SSTot != 0) return SSReg / SSTot;
	else return 0;
}


//exp. regression y=a*e^(b*x)
void ExpReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr)
{
	if (!(x && y && num && a && b)) return;
	//convert to liner
	double z[num];//temp
	for (unsigned int i = 0; i < num; i++)
		z[i] = log(y[i]);
	//liner regression
	SVLinerReg(x, z, num, a, b, rsqr);
	*a = exp(*a);
	//get R^2
	//if (rsqr) *rsqr = ExpReg_RSqr(x, y, num, *a, *b);
	return;
}

//R^2 of exp. reg.
double ExpReg_RSqr(double * x, double * y, const unsigned int num, double a, double b)
{
	if (!(x && y && num)) return 0;
	unsigned int i;	double y_avg = Avg(y, num), SSReg, SSTot;
	for (SSReg = SSTot = i = 0; i < num; i++)
	{
		SSReg = SSReg + (a * exp(b * x[i]) - y_avg) * (a * exp(b * x[i]) - y_avg);
		SSTot = SSTot + (y[i] - y_avg) * (y[i] - y_avg);
	}
	if (SSTot != 0) return SSReg / SSTot;
	else return 0;
}


//log. regression y=a*ln(x)+b
void LogReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr)
{
	if (!(x && y && num && a && b)) return;
	//convert to liner y=c+dt
	double t[num];//temp
	for (unsigned int i = 0; i < num; i++)
		t[i] = log(x[i]);
	//liner regression
	SVLinerReg(t, y, num, b, a, rsqr);
	//get R^2
	//if (rsqr) *rsqr = LogReg_RSqr(x, y, num, *a, *b);
	return;
}

//R^2 of log. reg.
double LogReg_RSqr(double * x, double * y, const unsigned int num, double a, double b)
{
	if (!(x && y && num)) return 0;
	unsigned int i;	double y_avg = Avg(y, num), SSReg, SSTot;
	for (SSReg = SSTot = i = 0; i < num; i++)
	{
		SSReg = SSReg + (a * log(x[i]) + b - y_avg) * (a * log(x[i]) + b - y_avg);
		SSTot = SSTot + (y[i] - y_avg) * (y[i] - y_avg);
	}
	if (SSTot != 0) return SSReg / SSTot;
	else return 0;
}


//to be continued


#ifdef __cplusplus
}
#endif // __cplusplus

//Thanks for reading![bi xin xin]
