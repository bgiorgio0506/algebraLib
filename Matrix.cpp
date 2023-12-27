/*
* Actual implementation of the Matrix object methos
* 
* Copyright Giorgio Bella 2022-2022
*/
#include "Matrix.h"
#include <math.h>

#define MAX_DIM 1000

//determinat 
long Matrix::det() {
	long det = 0;
	if (!this->isSquareMatrix()) return 0;
	else if (this->collumDim == 1) 
		return this->mat[0][0];
	else if (this->collumDim == 2) 
		return (this->mat[0][0] * this->mat[1][1]) - (this->mat[0][1] * this->mat[1][0]);
	else {
		double submatrix[MAX_DIM][MAX_DIM];
		for (int x = 0; x < this->collumDim; x++) {
			int subi = 0;
			for (int i = 1; i < this ->collumDim; i++) {
				int subj = 0;
				for (int j = 0; j <this->collumDim; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = this->mat[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * mat[0][x] * this->det(submatrix, this->collumDim - 1));
		}
	}
	return det;
}


/*
* det overload to call the function recursively
*/
long Matrix::det( double matrix[MAX_DIM][MAX_DIM], int dim) {
	long det = 0;
	if (!this->isSquareMatrix()) return 0;
	else if (this->collumDim == 1)
		return this->mat[0][0];
	else if (this->collumDim == 2)
		return (this->mat[0][0] * this->mat[1][1]) - (this->mat[0][1] * this->mat[1][0]);
	else {
		double submatrix[MAX_DIM][MAX_DIM];
		for (int x = 0; x < this->collumDim; x++) {
			int subi = 0;
			for (int i = 1; i < this->collumDim; i++) {
				int subj = 0;
				for (int j = 0; j < this->collumDim; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = this->mat[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * mat[0][x] * this->det(submatrix, this->collumDim - 1));
		}
	}
	return det;
}


/*
* if a matrix has the same collums and rows
*/
bool Matrix::isSquareMatrix() {
	if (this->collumDim == this->rowsDim) return true;
	else return false;
}

/*
* Find the trace of a matrix
*/

long Matrix::tr() {
	long traceSum = 0;

	if (!this->isSquareMatrix()) return;
	else if (this->collumDim == 1) return mat[0][0];
	else if (this->collumDim == 2) return mat[0][0] + mat[1][1];
	else {
		for (int i = 0; i < this->collumDim; i++) {
			traceSum += mat[i][i];
		}
		return traceSum;
	}

}

/*
* Multiply the matrix by a scalar number
*/
Matrix Matrix::scalarMultiplication(long number) {
	double resMat[MAX_DIM][MAX_DIM];
	for (int i = 0; i < this->rowsDim; i++) {
		for (int j = 0; j < this->collumDim; j++) {
			resMat[i][j] = this->mat[i][j] * number;
		}
	}

	return Matrix(this->rowsDim, this->collumDim, resMat);
}

/*
* Gaussian Elemination algorithm
*/
Matrix Matrix::gaussianElimination() {
	/* performing Gaussian elimination */
	double resMat[MAX_DIM][MAX_DIM];

	for (int i = 0; i < this->rowsDim - 1; i++)
	{
		for (int j = i + 1; j < this->collumDim; j++)
		{

			float f = this ->mat[j][i] /this-> mat[i][i];
			int iterations = 0;
			if (this->rowsDim > this->collumDim) iterations = this->rowsDim;
			else iterations = this->collumDim;
			for (int k = 0; k < iterations; k++)
			{
				resMat[j][k] = this ->mat[j][k] - f * this ->mat[i][k];
			}
		}
	}
	return Matrix(this->rowsDim, this->collumDim, resMat);
}

/*
* Reduce the matrixs to row inchelon form
*/

Matrix Matrix::rowInchelonForm() {
	double resMat[MAX_DIM][MAX_DIM];
	for (int i = 0; i < this->rowsDim; i++)
	{
		for (int j = i + 1; j < this->collumDim; j++)
		{
			if (fabsf(this->mat[i][i]) < fabsf(this->mat[j][i]))
			{
				int iterations = 0;
				if (this->rowsDim > this->collumDim) iterations = this->rowsDim;
				else iterations = this->collumDim;

				for (int k = 0; k < iterations; k++)
				{
					/* swapping mat[i][k] and mat[j][k] */
					resMat[i][k] = this->mat[i][k] + this->mat[j][k];
					resMat[j][k] = this->mat[i][k] - this->mat[j][k];
					resMat[i][k] = this->mat[i][k] - this->mat[j][k];
				}
			}
		}
	}
	return Matrix(this->rowsDim, this->collumDim, resMat);
}


/*
* Compute the inverse of a matrix
*/
Matrix Matrix::inverse() {
	long det = 0;
	if (!this->isSquareMatrix()) return;

	det = this->det();

	if (this->collumDim == 2 && det !=0) {
		const long temp = mat[0][0];
		mat[0][0] = mat[1][1];
		mat[1][1] = temp;
		mat[0][1] = -mat[0][1];
		mat[1][0] = -mat[1][0];
		return this->scalarMultiplication(1/det);
	}
	else if (this ->collumDim > 2 && det !=0) {
		// generalize with gaussJordan algo
		double res [MAX_DIM][MAX_DIM];
		Matrix adjointMatrix = this->adjoint();

		for (int i = 0; i < this->collumDim; i++) {
			for (int j = 0; i < this->collumDim; j++) {
				res[i][j] = adjointMatrix.mat[i][j] * 1 / det;
			}
		}

		return Matrix(this->collumDim, this->collumDim, res);

	}
}

Matrix Matrix::traspose() {
	double resMat[MAX_DIM][MAX_DIM];
	for (int i = 0; i < this->rowsDim; i++) {
		for (int j = 0; i < this->collumDim; j++) {
			this -> mat[i][j] = this -> mat[j][i];
		}
	}
	return Matrix(this->collumDim, this->rowsDim, resMat);
}

Matrix Matrix::getCofactorMaxtrix(int row, int collum) {

	if (!this->isSquareMatrix()) return;

	int rowCounter, collumCounter = 0;

	double cofactorMatrix[MAX_DIM][MAX_DIM];

	for (int i = 0; i < this->rowsDim; i++) {
		for (int j = 0; j < this->collumDim; j++) {
			if (i != row && j != collum) {
				cofactorMatrix[rowCounter][collumCounter ++] = this->mat[i][j];

				if (j == this->collumDim - 1) {
					rowCounter ++;
					collumCounter = 0;
				}
			}
				
		}
	}

	return Matrix(cofactorMatrix);
}


Matrix Matrix::adjoint() {
	double adjointMatrix[MAX_DIM][MAX_DIM];
	if (!this->isSquareMatrix()) return;
	else {
		int sign = 1; 
		for (int i = 0; i < this->rowsDim; i++) {
			for (int j = 0; j < this->rowsDim; j++) {
				Matrix cofactorMatrix =  this->getCofactorMaxtrix(i, j);
				sign = ((i + j) % 2 == 0) ? 1 : -1;
				adjointMatrix[i][j] = sign * this->det(cofactorMatrix.mat, this->rowsDim - 1);
			}
		}

		return Matrix(adjointMatrix);
	}

}

 Matrix Matrix::sumMatricies(Matrix m1, Matrix m2) {
	 if (m1.rowsDim != m2.rowsDim && m1.collumDim != m2.collumDim) return;

	 double resMat[MAX_DIM][MAX_DIM];

	 for (int i = 0; i < m1.rowsDim; i++) {
		 for (int j = 0; j < m1.rowsDim; j++) {
			 resMat[i][j] = m1.mat[i][j] + m2.mat[i][j];
		 }
	 }

	 return Matrix(m1.rowsDim, m1.collumDim, resMat);
}

 Matrix Matrix::multiplyMatricies(Matrix m1, Matrix m2) {
	 if (m1.collumDim != m2.rowsDim) return;

	 double res[MAX_DIM][MAX_DIM];
	 for (int i = 0; i < m1.collumDim; i++) {
		 for (int j = 0; j < m2.rowsDim; j++) {
			 res[i][j] = 0;

			 for (int k = 0; k < m2.rowsDim; k++) {
				 res[i][j] += m1.mat[i][k] * m2.mat[k][j];
			 }
		 }
	 }

	 return Matrix(m1.rowsDim, m2.collumDim, res);
 }

 Matrix Matrix::getSubMatrix(int fromRow, int toRow, int fromCol, int toCol){
	 if (fromRow > this->rowsDim || fromCol > this->collumDim) return;
	 
	 double res[MAX_DIM][MAX_DIM];
	 for (int i = 0; i < this->collumDim; i++) {
		 for (int j = 0; j < this->rowsDim; j++) {
			 if (fromCol >= i && fromRow >= j && toCol <=i && toRow<=j) {
				 res[i][j] = this->mat[i][j];
			 }
		 }
	 }

	 return Matrix(res);
 }