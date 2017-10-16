#pragma once
#include<fstream>
#include <ctime>
#include <omp.h> 
#define MY_SIZE 1000
#define ELEMENT_SIZE 1000
using namespace std;

int ** &createMatrix(int size);
void deleteMatrix(int** p);
void initMatrix(int ** p, int size);
void nullifyMatrix(int ** p, int size);
void printMatrix(int  **p, char* s);
//
//double prepareMatrix() {
//	
//
//
//	int m1[MY_SIZE][MY_SIZE], m2[MY_SIZE][MY_SIZE];
//	int m3[MY_SIZE][MY_SIZE];
//	
//	printf("press any key to generate m1\n");
//	_getch();
//	srand(clock());
//	for (int i = 0; i < MY_SIZE; i++) {
//		for (int j = 0; j < MY_SIZE; j++) {
//			
//			m1[i][j] = 
//				//rand();
//			rand() % ELEMENT_SIZE;
//		}
//	}
//
//	printf("press any key to generate m2\n");
//	_getch();
//	srand(clock());
//	for (int i = 0; i < MY_SIZE; i++) {
//		for (int j = 0; j < MY_SIZE; j++) {
//			m2[i][j] = rand() % ELEMENT_SIZE;
//		}
//	}
//
//	//НАЧАЛО
//	double start_time = omp_get_wtime();//clock(); // начальное время
//
//
//	//Первый вариант
//	//for (int i = 0; i < MY_SIZE; i++) {
//	//	for (int j = 0; j < MY_SIZE; j++) {
//	//		int buf = 0;
//	//		for (int k = 0; k < MY_SIZE; k++) {
//	//			buf += m1[i][k] * m2[k][j];
//	//		}
//	//		m3[i][j] = buf;
//	//	}
//	//}
//	////Второй вариант
//	//int dSize = MY_SIZE*MY_SIZE;
//	//for (int s = 0; s < dSize; s++) {
//	//	int i = (int)(s / MY_SIZE);
//	//	int j = s % MY_SIZE;
//	//	//cout << "i = " << i << "\t j = " << j << "\n";
//	//	int buf = 0;
//	//	for (int k = 0; k < MY_SIZE; k++) {
//	//		buf += m1[i][k] * m2[k][j];
//	//	}
//	//	m3[i][j] = buf;
//
//	//}
//	//Третий вариант
////
////	int dSize = MY_SIZE*MY_SIZE;
////
////#pragma omp parallel //for
////	{
////#pragma omp for
////		for (int s = 0; s < dSize; s++) {
////			int i = (int)(s / MY_SIZE);
////			int j = s % MY_SIZE;
////			//cout << "i = " << i << "\t j = " << j << "\n";int
////			int buf = 0;
////			for (int k = 0; k < MY_SIZE; k++) {
////				buf += m1[i][k] * m2[k][j];
////			}
////			m3[i][j] = buf;
////
////		}
////	}
//
//	int dSize = MY_SIZE*MY_SIZE;
//	int i, j, s, k;
////#pragma omp parallel //for
//	{
////#pragma omp for
//		for (int s = 0; s < dSize; s++) {
//			int i = (int)(s / MY_SIZE);
//			int j = s % MY_SIZE;
//			for (int k = 0; k < MY_SIZE; k++) {
//				m3[i][j] += m1[i][k] * m2[k][j];
//			}
//		}
//	}
//		//КОНЕЦ
//		//sleepcp(10);
//		double end_time = omp_get_wtime(); // конечное время
//		double search_time = end_time - start_time; // искомое время
//		return search_time;
//
//	//////////////////////////////////////////////////////////////////////////
//	//fstream out1;
//	//out1.open("printmatrix1.txt", ios_base::out);
//	//for (int i = 0; i < MY_SIZE; i++) {
//	//	for (int j = 0; j < MY_SIZE; j++) {
//	//		out1<<m1[i][j]<<"\t";
//	//	}
//	//	out1 << "\n";
//	//}
//	//out1.close();
//	//printf("\nm1  printed...\n");
//	//fstream out2;
//	//out2.open("printmatrix2.txt", ios_base::out);
//	//for (int i = 0; i < MY_SIZE; i++) {
//	//	for (int j = 0; j < MY_SIZE; j++) {
//	//		out2 << m2[i][j] << "\t";
//	//	}
//	//	out2 << "\n";
//
//	//}
//	//out2.close();
//	//printf("\nm2  printed...\n");
//	//fstream out3;
//	//out3.open("printmatrix3.txt", ios_base::out);
//	//for (int i = 0; i < MY_SIZE; i++) {
//	//	for (int j = 0; j < MY_SIZE; j++) {
//	//		out3 << m3[i][j] << "\t";
//	//	}
//	//	out3 << "\n";
//	//}
//	//out3.close();
//	//printf("\nm3  printed...\n");
//}

double multiply() {

	int **m1 = createMatrix(MY_SIZE);
	int **m2 = createMatrix(MY_SIZE);
	int **m3 = createMatrix(MY_SIZE);

	initMatrix(m1, MY_SIZE);
	initMatrix(m2, MY_SIZE);
	nullifyMatrix(m3, MY_SIZE);

	//printMatrix(m1, "printmatrix1.txt");
	//printMatrix(m2, "printmatrix2.txt");

	int threadsNum = 4;
	omp_set_num_threads(threadsNum);
	int i, j, k;
	double start_time = omp_get_wtime();//начальное время

#pragma omp parallel for shared(m1, m2, m3) private(i, j, k)
	for (i = 0; i < MY_SIZE; i++) {
		for (j = 0; j < MY_SIZE; j++) {
			for (k = 0; k < MY_SIZE; k++) {
				m3[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	double end_time = omp_get_wtime(); // конечное время
	
	double search_time = end_time - start_time; // искомое время
	//printMatrix(m3, "printmatrix3.txt");
	deleteMatrix(m1);
	deleteMatrix(m2);
	deleteMatrix(m3);

	return search_time;
}

int ** &createMatrix(int size) {
	int *storeMemory = new int[MY_SIZE*MY_SIZE];

	int **m1 = new int*[MY_SIZE];
	for (int i = 0; i < MY_SIZE; i++) {
		m1[i] = storeMemory + i*MY_SIZE;
	}
	return m1;
}
void initMatrix(int ** p, int size) {
	printf("press any key to generate matrix\n");
	_getch();
	srand(clock());
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			p[i][j] = rand() % ELEMENT_SIZE;
		}
	}
}
void nullifyMatrix(int ** p, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			p[i][j] = 0;
		}
	}
}
void printMatrix(int  **p, char* s) {
	fstream out1;
	out1.open(s/*"printmatrix1.txt"*/, ios_base::out);
	for (int i = 0; i < MY_SIZE; i++) {
		for (int j = 0; j < MY_SIZE; j++) {
			out1 << p[i][j] << "\t";
		}
		out1 << "\n";
	}
	out1.close();
	printf("\nmatrix  printed...\n");
}
void deleteMatrix(int** p) {
	delete[] * p;
	delete[] p;
}