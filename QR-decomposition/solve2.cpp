#include <iostream>
#include <math.h>
#include <cstring>
#include "header.h"

using namespace std;


void QR(int n, double*A, double* A_cos, double* A_sin, double d, double eps)
{
	int i, j, h;
	double mod, a;
	for (h = 0; h < d-1; ++h) //QR-разложение
			{
				mod = sqrt(A[h*n+h]*A[h*n+h] + A[(h+1)*n+h]*A[(h+1)*n+h]);
				if (mod > eps)
				{
					A_cos[h] = A[h*n+h]/mod;
					A_sin[h] = -A[(h+1)*n+h]/mod;
					for (j = h; j < d; ++j)
					{
						a = A[h*n+j];
						A[h*n+j] = a*A_cos[h] - A[(h+1)*n+j]*A_sin[h];
						A[(h+1)*n+j] = a*A_sin[h] + A[(h+1)*n+j]*A_cos[h];
					}
				}
				else
				{
					A_cos[h] = 1;
					A_sin[h] = 0;
				}
				
			}

	
	for (j = 0; j < d-1; ++j) //RQ
	{
		for (i = 0; i < d; ++i)
			{
				a = A[i*n+j];
				A[i*n+j] = a*A_cos[j] - A[i*n+j+1]*A_sin[j];
				A[i*n+j+1] = a*A_sin[j] + A[i*n+j+1]*A_cos[j];
			}
	}
}

int solve(int n, double* A, double* A_cos, double* A_sin, double* X, double epsilon) 
{
	int i, j, h, d;
	double sin, cos, sum, mod, a, last, s_k;
	double eps1 = norm_matrix(n, A)*1e-15;
	double eps2 = norm_matrix(n, A)*epsilon;
	double shift = 0;
	
	if (n==1)
	{
		X[0] = A[0];
		return 0;
	}
	
	for (h = 0; h < n-2; ++h) //Приведение к почтитреугольному виду
	{
		
		for (i = h+2; i < n; ++i)
		{
			mod = sqrt(A[(h+1)*n+h]*A[(h+1)*n+h]+A[i*n+h]*A[i*n+h]);
			if (mod <= eps1){A_cos[i] = 1; A_sin[i] = 0; continue;}
			A_cos[i] = A[(h+1)*n+h]/mod;
			A_sin[i] = -A[i*n+h]/mod;
			
			for (j = h; j < n; ++j)
			{
				a = A[(h+1)*n+j];
				A[(h+1)*n+j] = a*A_cos[i] - A[i*n+j]*A_sin[i];
				A[i*n+j] = a*A_sin[i] + A[i*n+j]*A_cos[i];
			}
		}
		
		
		
		for (i = h+2; i < n; ++i)
		{
			for (j = h; j < n; ++j)
			{
				a = A[j*n+h+1];
				A[j*n+h+1] = a*A_cos[i] - A[j*n+i]*A_sin[i];
				A[j*n+i] = a*A_sin[i] + A[j*n+i]*A_cos[i];
			}
		}
		
	} //Приведение к почтитреугольному виду

	
	
	for (d = n-1; d > 1; --d) //Поиск с.з.
	{	
		while(abs(A[d*n + d-1]) > eps2)
		{
			last = A[d*n + d-1];
			
			s_k = A[d*n+d];
			for (i = 0; i < d+1; ++i)
			{
				A[i*n+i] -= s_k + shift;
			}
		
			QR(n, A, A_cos, A_sin, d+1, eps1);
			
			
			for (i = 0; i < d+1; ++i)
			{
				A[i*n+i] += s_k;
			}
			
			if (abs(abs(A[d*n + d-1]) - abs(last)) < eps1){shift += eps2;}
		    	else{shift = 0;}
			
		}
		X[d] = A[d*n+d];
		
	}
	
	double D = (A[0*n+0]-A[1*n+1])*(A[0*n+0]-A[1*n+1]) + 4*A[0*n+1]*A[1*n+0];
	if (D < 0){return -3;}
	X[0] = (A[0*n+0] + A[1*n+1] + sqrt(D))/2;
	X[1] = (A[0*n+0] + A[1*n+1] - sqrt(D))/2;
	
	
	return 0;
}
