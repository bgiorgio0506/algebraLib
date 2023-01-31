#include "Matrix.h"
#include "Vector.h"
#pragma once
class SystemResolver:public Matrix
{
public:

	Matrix* sysMatrix;
	Matrix* resultMatrix;
	ResolverMethods method;
	Vector* resolution;
	int rowsDim, collumDim, systemGrade = 0;

	SystemResolver(double coefMatrix[MAX_DIM][MAX_DIM],int systemGrade, ResolverMethods method){
		this->rowsDim = sizeof(coefMatrix) / sizeof(coefMatrix[0]);
		this->collumDim = sizeof(coefMatrix) / sizeof(coefMatrix[0][0]);
		this->sysMatrix = new Matrix(this->rowsDim, this->collumDim, coefMatrix);
		this->method = method;
		this->systemGrade = systemGrade;

	}

	Vector resolveSystem() {
		switch (this->method) {
			case (GAUSS_ELIMINATION):
				break;
			case (QR_FACTORIZATION):
				break;
			case (LU_FACTORIZATION):
				break;
		}
	}

private:

	Vector backSubstitution() {
		double resArr[collumDim];
		for (int i = rowsDim; i >= 0; i--) {
			resArr[i] = sysMatrix->mat[i][collumDim];
			for (int j = 0; j < collumDim; j++) {
				if (i != j) {
					resArr[i] = resArr[i] - sysMatrix->mat[i][j] * resArr[j];
				}
			}

			resArr[i] = resArr[i] / sysMatrix->mat[i][i];
		}

		this->resolution = new Vector(rowsDim, resArr)
	}


public: 
	static bool linearDependecy(Vector v1, Vector v2){

	}
};


enum ResolverMethods
{
	GAUSS_ELIMINATION = 1,
	LU_FACTORIZATION = 2,
	QR_FACTORIZATION = 3
};
