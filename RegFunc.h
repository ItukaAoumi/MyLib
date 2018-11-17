/*
This is a library of regression functions.
Including: Single-Variable Liner, Hyperbolic, Exponential, Logarithmic;
Multi-Variable Liner;

Plan: Ji Qi Yi
Program: Ituka Aoumi
Review: Sai Ya
Produce: Code A Live
Thanks for @umr05, @emmm_zark
Code A Live, 2018
*/


//Do not include me more than twice!
#pragma once
#ifndef RegFunc_H
#define RegFunc_H

//Can be used in cpp!
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//the average(mean) of a sequence
double Avg(double * arr, unsigned int num);

//R^2 of a regression function
double RSqr(double * x, double * y, double * y_pred, unsigned int num);


/*
Single Variable Liner Regression y=a+bx
params:
x and y: pointer of data array
num: number of data
a and b: output a and b
rsqr: output R^2 (optional, set 0 if not needed)
*/
void SVLinerReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr);

//R^2 of Single Variable Liner Regression
double SVLinerReg_RSqr(double * x, double * y, const unsigned int num, double a, double b);


//Hyperbolic Regression y=1/(a+bx)
void HypReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr);

//R^2 of hyp. reg.
double HypReg_RSqr(double * x, double * y, const unsigned int num, double a, double b);


//exp. regression y=a*e^(b*x)
void ExpReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr);

//R^2 of exp. reg.
double ExpReg_RSqr(double * x, double * y, const unsigned int num, double a, double b);


//log. regression y=a*ln(x)+b
void LogReg(double * x, double * y, const unsigned int num, double * a, double * b, double * rsqr);

//R^2 of log. reg.
double LogReg_RSqr(double * x, double * y, const unsigned int num, double a, double b);


/*
Multi Variable Liner Regression y=SUM(a[i]*x[i])
Using gradient descending.
Input Data Matrix:
[x[0,0] x[0,1] ... x[0,m] y[0]]
[x[1,0] x[1,1] ... x[1,m] y[1]]
...
[x[n-1,0] x[n-1,1] ... x[n-1,m] y[n-1]]
Rows=n, Columns=m+2;
Parameters:
a[0] a[1] ... a[m]
x[i,0]=1, a[0] is the constant
*/
extern umiMat_p;
void MVLinerReg(umiMat_p dat, double * parm);

double MVLinerReg_Drv(umiMat_p dat, double * parm, unsigned int num);


//to be continued


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !RegFunc_H

//Thanks for reading![bi xin xin]
