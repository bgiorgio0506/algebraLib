#include "Matrix.h"
#include "Vector.h"
#pragma once
class SystemResolver:public Matrix
{
public:

	Matrix* sysMatrix;
	ResolverMethods method;
	Vector resolution;
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
			case (GAUSS_SEIDEL):
				break;
			case (BACK_SUB):
				break;
			case (CRAMER):
				break;
		}
	}

private:

	void gaussSeidel() {

	}

};


enum ResolverMethods
{
	GAUSS_SEIDEL = 1,
	BACK_SUB = 2,
	CRAMER = 3,
};
