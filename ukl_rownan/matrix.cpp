#include "matrix.h"

void Complement(double** pTab0, double** pTabI, int nRow, int nCol, int nDim);
void CompMatrix(double** pTabD, double** pTab, int nDim);
void TransMatrix(double** pTab, int nDim); 



//-----------------------------------------------------------------

int CreateMatrix(double*** pTab, int nSize) 
{
	double** t = *pTab = (double**)calloc(nSize, sizeof(double*));
	if (!t) 
	{
		printf("\nUnable to allocate memory\n");
		return -1;
	}
	for (int i = 0; i < nSize; i++)
	{
		*t++= (double*)calloc(nSize, sizeof(double));
		if (!t) 
		{
			printf("Unable to allocate memory!");
			return -1;
		}
	}
	return 1;
}


void DeleteMatrix(double*** pTab, int nSize) 
{
	double ** m = *pTab;
	for (int i = 0; i < nSize; i++)
	{
		free(*m++);
	}
	free(*pTab);
	*pTab = NULL;
}

void InverseMatrix(double** pTab, double** pInv, int nSize, double det)
{
	CompMatrix(pTab, pInv, nSize);
	TransMatrix(pInv, nSize);
	for (int i = 0; i < nSize; i++)
	{
		double* p= *pInv++;
		for (int j = 0; j < nSize; j++)
		{
			*p++ /= det;
		}
	}
}

double Det(double** pTab, int nSize) 
{
	double det = 0.0;
	double** m;
	if (nSize == 1)
	{
		return pTab[0][0];
	}
	else if (nSize == 2)
	{
		return pTab[0][0] * pTab[1][1] - pTab[1][0] * pTab[0][1];
	}
	double coef = 1;
	CreateMatrix(&m, nSize - 1);
	if (!m)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	for (int i = 0; i < nSize; i++)
	{
		Complement(pTab,m, 0, i, nSize);
		det += coef*pTab[0][i] * Det(m, nSize - 1);
		coef = -coef;
	}
	DeleteMatrix(&m, nSize - 1);
	return det;
}



void LayoutEqu(double** pInv, double* pB, double* pRes, int nSize) 
{
	for (int i = 0; i < nSize; i++)
	{
		double *p1 = pB;
		double* m1 = *pInv++;
		for (int j = 0; j < nSize; j++)
		{
			*pRes += *m1++ * *p1++;
		}
		pRes++;
	}
}

void PrintMatrix(double** pTab, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		double * v = pTab[i];
		for (int j = 0; j < nSize; j++)
			printf(" %lf", *v++);
		printf("\n");
	}
	printf("\n");
}

void PrintTab(double* t, int nSize)
{
	double *v = t;
	for (int i = 0; i < nSize; i++)
	{
		printf(" %lf", *v++);
	}
	v = t;
	printf("\n\n");
}

void ReadMatrix(FILE* f1, double** pTab, double* ww, int nSize)
{
	double * p = ww;
	for (int i = 0; i < nSize; i++)
	{
		double* v = *pTab++;
		for (int j = 0; j < nSize; j++)
		{
			fscanf(f1, "%lf", v++);
		}
		fscanf(f1, "%lf", p++);
	}
	fclose(f1);

}

//-----------------------------------------------------

void Complement(double** pTab, double** pTab0, int nRow, int nCol, int nDim) //pTab0-wyjsciowa, pTab-wejsciowa
{
	double** m = pTab; //wejsciowe
	double** m1 = pTab0; //wyjsciowe
	for (int i = 0; i < nDim; i++,m++)
	{
		if (i == nRow)
			continue;
		double* m1p=*m1++;
		double* mp = *m;
		for (int j = 0; j < nDim; j++,mp++)
		{
			if (j == nCol)
				continue;
			*m1p++ = *mp;
		}
	}
}

void CompMatrix(double** pTabD, double** pTab, int nDim)
{
	double** m = pTab;
	double **m1;
	CreateMatrix(&m1, nDim);
	if (!m1)
	{
		printf("Unable to allocate memory!");
		return;
	}
	
	for (int i = 0; i < nDim; i++)
	{
		double coef = (i % 2) ? -1 : 1;
		double* m2 = *m++;
		for (int j = 0; j < nDim; j++)
		{
			Complement(pTabD,m1, i, j, nDim);
			*m2++ =coef*Det(m1, nDim - 1);
			coef = -coef;
		}
	}
	DeleteMatrix(&m1, nDim);
}

void TransMatrix(double** pTab, int nSize) 
{
	double temp;
	double**t = pTab;
	for (int i = 0; i < nSize-1; i++)
	{
		double* ti = (*t++ + i + 1);
		for (int j = i + 1; j< nSize; j++)
		{
			temp = *ti;
			*ti++ = pTab[j][i];
			pTab[j][i] = temp;
		}
	}
}

