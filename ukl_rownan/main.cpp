// ukl_rownan.cpp : Defines the entry point for the console application.
#include "matrix.h"
#define _DEBUG_

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("ERROR! There is no parameters!\n");
	}
	int nDim;
	FILE * f1;
	f1 = fopen (argv[1],"r");
	if (!f1)                 
	{
		printf("Error! File not opened\n\n");
		return 1;
	}
	fscanf(f1, "%d", &nDim);
#ifdef _DEBUG_ 
	printf("%d\n", nDim);
#endif
	double** pTab=NULL;
	CreateMatrix(&pTab, nDim);
	if (!pTab)
	{
		printf("Unable to allocate memory!");
		return -1;
	}

	double* ww = (double*)calloc(nDim, sizeof(double));
	if (!ww)
	{
		printf("Unable to allocate memory!");
		return -1;
	}

	ReadMatrix(f1, pTab, ww, nDim);
#ifdef _DEBUG_
	PrintMatrix(pTab, nDim);
	PrintTab(ww, nDim);
#endif

	double det = Det(pTab, nDim);
	if (fabs(det) < 1e-10)
	{
		printf("Cannot invert matrix -> det=0 ");
		return 2;
	}
#ifdef _DEBUG_
	printf("det=%lf \n", det);
#endif
	double** pInv = NULL;
	CreateMatrix(&pInv, nDim);
	if (!pInv)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	InverseMatrix(pTab, pInv, nDim, det);
#ifdef _DEBUG_
	PrintMatrix(pInv, nDim);
#endif

	double* res = (double*)calloc(nDim, sizeof(double)); 
	if (!res)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	LayoutEqu(pInv, ww, res, nDim);

	PrintTab(res, nDim);
	free(ww);
	free(res);
	DeleteMatrix(&pTab, nDim);
	DeleteMatrix(&pInv, nDim);
	
	return 0;
}



