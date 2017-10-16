#pragma once
#include<stdio.h>
#include <time.h>
#include<iostream>
#include<conio.h>
#include <omp.h> 
#define SIZE 100000
void sleepcp(int milliseconds) // cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}
void f1() {
#pragma omp parallel

	{
		printf("hello\n");
	}

}
void f2() {
	int a[SIZE];
	for (int i = 0; i < SIZE; i++) {
		a[i] = 1;
	}
	int sum = 0;//вне блоkа pragma

#pragma omp for

	for (int i = 0; i < SIZE; i++) {
		sum += a[i];
	};

	printf("%d", sum);
}

void f3() {
	int a[SIZE];
	for (int i = 0; i < SIZE; i++) {
		a[i] = 1;
	}
	int sum = 0;//вне блоkа pragma - общая переменная

#pragma omp parallel //for
	{
#pragma omp for
		for (int i = 0; i < SIZE; i++) {
			#pragma omp critical
			{
				sum += a[i];
			}
		}
	}

	printf("%d", sum);
}

void f3_() {
	int a[SIZE];
	for (int i = 0; i < SIZE; i++) {
		a[i] = 1;
	}
	int sum = 0;//вне блоkа pragma - общая переменная

//#pragma omp parallel //for
	{
//#pragma omp for
		for (int i = 0; i < SIZE; i++) {
//#pragma omp critical
			{
				sum += a[i];
			}
		}
	}

	printf("%d", sum);
}


void f4() {
	int a[SIZE];
	for (int i = 0; i < SIZE; i++) {
		a[i] = 1;
	}
	int sum = 0;//вне блоkа pragma - общая переменная
#pragma omp parallel reduction(+:sum)
	{
		#pragma omp for 
		for (int i = 0; i < SIZE; i++) {


			sum += a[i];

		}
	}

	printf("%d", sum);
}

void f5() {

#pragma omp parallel

	{

#pragma omp for

		for (int n = 0; n<SIZE; ++n) printf("\n %d", n);

	}

	printf(".n");
}

void f6() {
	int n;

#pragma omp parallel 
	{
		//#pragma omp critical 
		{
			n = omp_get_thread_num();;
			printf("Thread %d\n", n);
		}
	}
}
void f7() {
#pragma omp parallel num_threads(2)
	{
		sleepcp(3000);
		printf("Hello World\n");
	}
}