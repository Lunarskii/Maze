#ifndef SRC_LOGIC_S21_MATRIX_OOP_H_
#define SRC_LOGIC_S21_MATRIX_OOP_H_

#include <cmath>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

  // additional private methods
  double calcDeterminant();  // A function for calculating the determinant
  void calcMinor(int row, int column,
                 S21Matrix& other);  // A function for calculating the minor
  void memoryAllocation();  // A function for allocating memory for the matrix
 public:
  S21Matrix();                        // Default constructor
  S21Matrix(int rows, int cols);      // Parameterized constructor
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor
  ~S21Matrix();                       // Destructor

  // methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // accessors
  int getRows();
  int getCols();
  void setRows(int rows);
  void setCols(int cols);

  // additional public methods
  void validateMatrixSize() const;  // A function to check whether a matrix with
                                    // non-zero dimensions has been created
  void validateMatrixSize(const S21Matrix& other)
      const;  // A Function for checking that the matrices are equal in size.
              // There is also a check that the matrices have been created.
  void validateSquareMatrix()
      const;  // A function to check whether the matrix is square
  void copyMatrix(
      const S21Matrix& other);  // A function for copying the values of the
                                // other matrix to the this matrix
  void fillMatrix(
      double* values);  // A function for filling the matrix with values

  // operators overloading
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double& operator()(int row, int col);
};

#endif  // SRC_LOGIC_S21_MATRIX_OOP_H_
