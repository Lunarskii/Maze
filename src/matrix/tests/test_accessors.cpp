#include "test_core.h"

TEST(ACCESSORS, GET_ROWS) {
  S21Matrix M0;
  S21Matrix M1(1, 1);
  S21Matrix M2(2, 1);
  S21Matrix M3(3, 1);

  ASSERT_EQ(M0.getRows(), 0);
  ASSERT_EQ(M1.getRows(), 1);
  ASSERT_EQ(M2.getRows(), 2);
  ASSERT_EQ(M3.getRows(), 3);
}

TEST(ACCESSORS, GET_COLS) {
  S21Matrix M0;
  S21Matrix M1(1, 1);
  S21Matrix M2(1, 2);
  S21Matrix M3(1, 3);

  ASSERT_EQ(M0.getCols(), 0);
  ASSERT_EQ(M1.getCols(), 1);
  ASSERT_EQ(M2.getCols(), 2);
  ASSERT_EQ(M3.getCols(), 3);
}

TEST(ACCESSORS, SET_ROWS_EXPANSION) {
  S21Matrix M1(2, 2);
  S21Matrix result(4, 2);
  double values_M1_1[4] = {1, 2, 3, 4};
  double values_result[8] = {1, 2, 3, 4, 0, 0, 0, 0};

  M1.fillMatrix(values_M1_1);
  result.fillMatrix(values_result);
  M1.setRows(4);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(ACCESSORS, SET_ROWS_DECREASE) {
  S21Matrix M1(2, 2);
  S21Matrix result(1, 2);
  double values_M1_1[4] = {1, 2, 3, 4};
  double values_M1_2[2] = {1, 2};

  M1.fillMatrix(values_M1_1);
  result.fillMatrix(values_M1_2);
  M1.setRows(1);

  ASSERT_EQ(M1.EqMatrix(result), true);
}

TEST(ACCESSORS, SET_COLS_EXPANSION) {
  S21Matrix M1(2, 2);
  S21Matrix result(2, 4);
  double values_M1_1[4] = {1, 2, 3, 4};
  double values_result[8] = {1, 2, 0, 0, 3, 4, 0, 0};

  M1.fillMatrix(values_M1_1);
  result.fillMatrix(values_result);
  M1.setCols(4);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(ACCESSORS, SET_COLS_DECREASE) {
  S21Matrix M1(2, 2);
  S21Matrix result(2, 1);
  double values_M1_1[4] = {1, 2, 3, 4};
  double values_M1_2[2] = {1, 3};

  M1.fillMatrix(values_M1_1);
  result.fillMatrix(values_M1_2);
  M1.setCols(1);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
