#ifndef _MATRIX_INCLUDE_
#define _MATRIX_INCLUDE_

#include <stdio.h>
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>


int CreateMatrix(double*** pTab, int nSize); //wywolujemy funkcje kreujaca z adresem to pMx
void DeleteMatrix(double*** pTab, int nSize); //zwalnia pamiec
void InverseMatrix(double** pTab, double** pInv, int nSize, double det); //odwraca macierz, potrzebujemy wyznacznik
double Det(double ** pTab, int nSize); //oblicza wyznacnzik macierzy
void LayoutEqu(double **pInv, double* pB, double* pRes, int nSize); //rozwiazywanie ukladu rownan
void PrintMatrix(double** pTab, int nSize); //drukowanie macierzy dwuwymiarowej o danym rozmiarze, bedziemy jej uzywac do wydrukow kontrolnych
void ReadMatrix(FILE* f1, double** pTab, double* ww, int nSize);
void PrintTab(double* pTab, int nSize);

#endif