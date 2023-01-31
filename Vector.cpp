#include "Vector.h"
#include <math.h>

double Vector::vectorModule() {
	double sum = 0;
	double n = 0; 
	for (int i = 0; i < this->vLen; i++) {
		sum += pow(this->v[i], 2);
	}

	return sqrt(sum);
}

double Vector::dotProduct(Vector v1, Vector v2) {
	if (v1.vLen != v2.vLen) return;
	
	double sum = 0;
	for (int i = 0; i < v1.vLen; i++) {
		sum += v1.v[i] * v2.v[i];
	}

	return sum;
}


double Vector::angleRespectVector(Vector v1, Vector v2) {
	if (v1.vLen != v2.vLen) return;
	
	double dotProd = Vector::dotProduct(v1, v2);
	double vectorModuleProd = v1.vectorModule() * v2.vectorModule();

	if (dotProd == 0 || vectorModuleProd == 0) return;
	else return acos(dotProd / vectorModuleProd);
}



Vector Vector::crossProduct(Vector v1, Vector v2) {

	if (v1.vLen != 3 || v1.vLen != v2.vLen) return;

	double res[MAX_DIM];


	res[0] = v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1];
	res[1] = v1.v[2] *v2.v[0] - v1.v[0] * v2.v[2];
	res[2] = v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0];

	return Vector(3, res);
}