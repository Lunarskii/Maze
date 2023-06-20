#include "s21_matrix.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  this->validateMatrixSize();
  other.validateMatrixSize();

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
        return false;
      }
    }
  }

  return true;
}

S21Matrix S21Matrix::Transpose() {
  this->validateMatrixSize();

  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  this->validateMatrixSize();
  this->validateSquareMatrix();

  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        minor.calcMinor(i, j, *this);
        result.matrix_[i][j] = minor.Determinant() * pow(-1, i + j);
      }
    }
  }

  return result;
}

void S21Matrix::calcMinor(int row, int column, S21Matrix &other) {
  for (int i = 0, minor_i = 0; i < other.rows_; i++) {
    if (i == row) continue;
    for (int j = 0, minor_j = 0; j < other.cols_; j++) {
      if (j == column) continue;
      matrix_[minor_i][minor_j] = other.matrix_[i][j];
      minor_j++;
    }
    minor_i++;
  }
}

double S21Matrix::Determinant() {
  this->validateMatrixSize();
  this->validateSquareMatrix();
  double det = 0;

  if (rows_ == 1) {
    det = matrix_[0][0];
  } else {
    det = calcDeterminant();
  }

  return det;
}

double S21Matrix::calcDeterminant() {
  double det = 0;

  if (rows_ == 1) {
    det = matrix_[0][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0, sign = 1; i < rows_; i++, sign *= -1) {
      minor.calcMinor(i, 0, *this);
      det += sign * matrix_[i][0] * minor.calcDeterminant();
    }
  }

  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  this->validateMatrixSize();
  this->validateSquareMatrix();
  S21Matrix result(rows_, cols_);

  if (double det = Determinant(); fabs(det) > 1e-6) {
    if (rows_ == 1) {
      result.matrix_[0][0] = 1 / det;
    } else {
      result = CalcComplements();
      result = result.Transpose();
      result.MulNumber(1.0 / det);
    }
  } else {
    throw std::range_error("The determinant is 0");
  }

  return result;
}
