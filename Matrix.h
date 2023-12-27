/*
* Actual implementation of the Matrix object methos
* 
* Copyright Giorgio Bella 2022-2023
*/

#include <limits.h>

#define MAX_DIM 1000


class Matrix
{
	
private:
	int collumDim;
	int rowsDim;

	long det(double mat[MAX_DIM][MAX_DIM], int dim);

	public:
		double mat[MAX_DIM][MAX_DIM];

		Matrix() = default; //tell C++ this is default constructor;

		//constructor of the class
		Matrix(int rowsDim, int collumDim, double matrix[MAX_DIM][MAX_DIM]) {
			this->collumDim = collumDim;
			this->rowsDim = rowsDim;
			//load the matrix consider filling the matrix rows by rows
			for (int j = 0; j < this->rowsDim; j++) {
				for (int k = 0; k < this->collumDim; k++) {
					this->mat[j][k] = matrix[j][k];
				}
			}
		}

		Matrix(double matrix[MAX_DIM][MAX_DIM]) {
			int rowDim = sizeof(matrix)/sizeof(matrix[0]);
			int colDim = sizeof(matrix[0])/sizeof(matrix[0][0]);
			this->collumDim = colDim;
			this->rowsDim = rowDim;

			for (int j = 0; j < this->rowsDim; j++) {
				for (int k = 0; k < this->collumDim; k++) {
					this->mat[j][k] = matrix[j][k];
				}
			}
		
		}

		//deconstructor 
		virtual ~Matrix() {
			this->collumDim = 0;
			this->rowsDim = 0;
		}

		long det();

		long tr();

		bool isSquareMatrix();

		Matrix getCofactorMaxtrix(int row, int collum);

		Matrix adjoint();
	
		Matrix scalarMultiplication(long number);

		Matrix inverse();

		Matrix traspose();

		Matrix gaussianElimination();

		Matrix rowInchelonForm();

		Matrix getSubMatrix(int fromRow, int toRow, int fromCol, int toCol);

		static Matrix sumMatricies(Matrix m1, Matrix m2);

		static Matrix multiplyMatricies(Matrix m1, Matrix m2);

};
	
