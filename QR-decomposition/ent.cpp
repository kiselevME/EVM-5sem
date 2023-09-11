#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include "header.h"
using namespace std;

double f(int, int, int, int);

double f(int k, int n, int i, int j)
{
	if (k == 1)
        {
        	return(n - std::max (i+1,j+1) + 1);
        }
        
        else if (k == 2)
        {
        	if (i == j){return 2;}
        	else if (abs(i-j) == 1){return -1;}
        	else{return 0;}
        }
        
        else if (k == 3)
        {
        	if ((i == j)&&(j+1 < n)){return 1;}
        	else if (j+1 == n){return i+1;}
        	else if (i+1 == n){return j+1;}
        	else{return 0;}
        }
        
        else if (k == 4)
        {
        	return(1/(double)(i+j+1));
        }
        return(0);
}

int entermatrix(double* A, char* input, int n, int form)
{
	int i, j;
        
        
        if (form == 0)
        {
        	FILE *in;
        	in = fopen(input, "rt"); 
        	if(in == NULL)
        	{
        		fclose(in);
        		return(-1);
        	}
        	
		for (i = 0; i < n*n; ++i)
		{
			if(fscanf(in, "%lf", &A[i]) != 1)
			{
				fclose(in);
				return(-2);
			}
		}
		
		fclose(in);
        }
        
        else
        {
        	for (i = 0; i < n; ++i)
        	{
        		for (j = 0; j < n; ++j)
        		{
        			A[i*n+j] = f(form, n, i, j);
        		}
        	}
        }
        
        
	return 0;
}
