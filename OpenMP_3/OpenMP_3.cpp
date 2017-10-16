// OpenMP_3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<stdio.h>
//#include <time.h>
//#include <ctime>
#include<iostream>
#include<conio.h>
//#include <omp.h> 
#include"functions.h"
#include"matrix.h"
using namespace std;

int main()
{
	//double time = prepareMatrix();
	double time = multiply();


	printf("\nTIME = %f", time);

	_getch();
	return 0;
}

