#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "header.h"

using namespace std;

double norm_matrix(int n, double* Prod)
{
	int i, j;
	double sum, result = 0;
	for (i = 0; i < n; ++i)
	{
		sum = 0;
		for (j = 0; j < n; ++j)
		{
			sum += abs(Prod[i*n+j]);
		}
		if (sum > result)
		{
			result = sum;
		}
	}
	return result;
}

double norma1(int n, double* A, double* X)
{
	int i;
	double result = 0;
	for (i = 0; i < n; ++i)
	{
		result += A[i*n+i];
		result -= X[i];
	}
	return abs(result);
}

double norma2(int n, double* A, double* X)
{
	int i, j;
	double result = 0, len = 0;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			len += A[i*n+j]*A[i*n+j];
		}
		result += X[i]*X[i];
	}
	return abs(sqrt(result)-sqrt(len));
}
