#include "s21_matrix.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  memoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  new (this) S21Matrix(other.rows_, other.cols_);
  copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != 0) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != 0) delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows >= 1 && rows_ != rows) {
    S21Matrix result(rows, cols_);
    result.copyMatrix(*this);
    *this = result;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols >= 1 && cols_ != cols) {
    S21Matrix result(rows_, cols);
    result.copyMatrix(*this);
    *this = result;
  }
}

void S21Matrix::validateMatrixSize() const {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Matrix size is invalid");
  }
}

void S21Matrix::validateMatrixSize(const S21Matrix &other) const {
  this->validateMatrixSize();
  other.validateMatrixSize();
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Matrices of unequal sizes");
  }
}

void S21Matrix::validateSquareMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square");
  }
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_ && i < other.rows_; i++) {
    for (int j = 0; j < cols_ && j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::memoryAllocation() {
  this->validateMatrixSize();

  if (matrix_ = new double *[rows_] {}; matrix_ != 0) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] = new double[cols_]{}; matrix_[i] == 0) {
        this->~S21Matrix();
      }
    }
  }
}

void S21Matrix::fillMatrix(double *values) {
  for (int i = 0, iv = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++, iv++) {
      matrix_[i][j] = values[iv];
    }
  }
}
