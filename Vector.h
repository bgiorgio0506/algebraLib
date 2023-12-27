#include "Matrix.h"

#pragma once
class Vector
{
public:
	double v[MAX_DIM];
	int vLen; 

	//Methods
	double vectorModule();
	double vModuleSquared();
	static double angleRespectVector(Vector v1, Vector v2);
	static double dotProduct(Vector v1, Vector v2);
	static Vector crossProduct(Vector v1, Vector v2);


	Vector(int dim, double numbers[MAX_DIM]) {
		if (dim == 0) return;
		this->vLen = dim;

		for (int i = 0; i < dim; i++) {
			v[i] = numbers[i];
		}
	}

	Vector() = default;
};

