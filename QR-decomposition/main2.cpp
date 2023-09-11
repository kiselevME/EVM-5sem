#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <cmath>
#include "header.h"
#include <time.h>

using namespace std;

int main(int argn, char **args) 
{
    if (argn < 4) // Проверки на некорректный ввод
    {
    	cout << "Некорректные входные данные";
    	return -1;
    }

    
    if (((stoi(args[4]) == 0) && (argn == 6)) || (((0 < stoi(args[4])) && (stoi(args[4]) < 5)) && (argn == 5)))
    {}
    else
    {
    	cout << "Некорректные входные данные";
    	return -1;
    }
    
    clock_t start, end;
    
    double *A;
    double *A_cos;
    double *A_sin;
    double *CopyA;
    double *X;
    int i, j, error;
    
    int n = stoi(args[1]); //считываем переменные
    int m = stoi(args[2]);
    double eps = stod(args[3]);
    int form = stoi(args[4]);

    if (n <= 0){cout<<"Некорректные входные данные"; return -1;}
    if (m > n||m <= 0){cout<<"Некорректные входные данные"; return -1;}
    

    try
    {
	    A = new double[n*n];
	    CopyA = new double[n*n];
	    
	    error = entermatrix(A, args[5], n, form); // ENTERMATRIX
	    
	    
	    if (error == -1)
	    {
	    	cout << "Ошибка при открытии файла";
	    	delete [] A;
	    	return -1;
	    }
	    else if (error == -2)
	    {
	    	cout << "Ошибка при чтении файла";
	    	delete [] A;
	    	return -1;
	    }
	    
	    outmatrix(n, n, m, A); // OUTMATRIX A
	    cout<<endl;
	    
	    
	    for (i = 0; i < n; ++i)
	    {
	    	for (j = 0; j < n; ++j)
	    	{
	    		CopyA[i*n+j] = A[i*n+j];
	    	}
	    }
	    
	    A_cos = new double[n];
	    A_sin = new double[n];
	    X = new double[n];
	    
	    start = clock();
	    error = solve(n, A, A_cos, A_sin, X, eps); // SOLVE
	    end = clock();
	   
	    outmatrix(n, 1, m, X); // OUTMATRIX X
	    
	    printf("Время работы программы = %10.3e ", ((double)(end - start))/((double)CLOCKS_PER_SEC));
	    cout << endl;
	    
	    if (error == -3)
	    {
	    	cout << "Комплексные с.з.";
		delete [] A;
		delete [] X;
    		delete [] CopyA;
    		delete [] A_cos;
    		delete [] A_sin;
		return -1;
	    }
	    

	    
	    printf("Норма невязки в первом инварианте= %10.3e ", norma1(n, CopyA, X)); // NORM1
	    cout << endl;
	    printf("Норма невязки во втором инварианте= %10.3e ", norma2(n, CopyA, X)); // NORM2
	    cout << endl;
	    
	    
    }
    catch(const exception& e)
    {
    	std::cerr << e.what() << endl;
    	delete [] A;
    	delete [] X;
    	delete [] CopyA;
    	delete [] A_cos;
    	delete [] A_sin;
    	return -3; 
    }
    
    delete [] A;
    delete [] X;
    delete [] CopyA;
    delete [] A_cos;
    delete [] A_sin;
    
    return 0;
}

