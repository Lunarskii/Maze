#include "test_core.h"

TEST(OPERATOR_PLUS, PLUS_3x3_2x2) {
  try {
    S21Matrix M1(3, 3);
    S21Matrix M2(2, 2);

    M1.SumMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrices of unequal sizes");
  }
}
TEST(OPERATOR_PLUS, PLUS_3x3_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix M1_TEST(3, 3);
  S21Matrix M2_TEST(3, 3);
  S21Matrix M3;
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {2, 4, 6, 8, 10, 12, 14, 16, 18};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M1_TEST.fillMatrix(values_M1);
  M2_TEST.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M3 = M1 + M2;

  ASSERT_EQ(M3.EqMatrix(result), true);
  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
  ASSERT_EQ(M2.EqMatrix(M2_TEST), true);
}

TEST(OPERATOR_MINUS, MINUS_3x3_2x2) {
  try {
    S21Matrix M1(3, 3);
    S21Matrix M2(2, 2);

    M1.SubMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrices of unequal sizes");
  }
}
TEST(OPERATOR_MINUS, MINUS_3x3_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix M1_TEST(3, 3);
  S21Matrix M2_TEST(3, 3);
  S21Matrix M3;
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {0};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M1_TEST.fillMatrix(values_M1);
  M2_TEST.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M3 = M1 - M2;

  ASSERT_EQ(M3.EqMatrix(result), true);
  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
  ASSERT_EQ(M2.EqMatrix(M2_TEST), true);
}

TEST(OPERATOR_MUL_MATRIX, MUL_3x3_2x2) {
  try {
    S21Matrix M1(3, 3);
    S21Matrix M2(2, 2);

    M1.MulMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "The matrices have unsuitable dimensions");
  }
}
TEST(OPERATOR_MUL_MATRIX, MUL_3x3_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix M1_TEST(3, 3);
  S21Matrix M2_TEST(3, 3);
  S21Matrix M3;
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {30, 36, 42, 66, 81, 96, 102, 126, 150};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M1_TEST.fillMatrix(values_M1);
  M2_TEST.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M3 = M1 * M2;

  ASSERT_EQ(M3.EqMatrix(result), true);
  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
  ASSERT_EQ(M2.EqMatrix(M2_TEST), true);
}

TEST(OPERATOR_MUL_NUMBER, MUL_3x3_3x3) {
  S21Matrix M1(3, 3);
  double number = 5;
  double number_test = number;
  S21Matrix M1_TEST(3, 3);
  S21Matrix M3;
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {5, 10, 15, 20, 25, 30, 35, 40, 45};

  M1.fillMatrix(values_M1);
  M1_TEST.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M3 = M1 * number;

  ASSERT_EQ(M3.EqMatrix(result), true);
  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
  ASSERT_EQ(number, number_test);
}

TEST(OPERATOR_EQUAL, EQ_3x3_2x2) {
  S21Matrix M1(3, 3);
  S21Matrix M2(2, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);

  ASSERT_EQ(M1 == M2, false);
}
TEST(OPERATOR_EQUAL, EQ_3x3_3x3_1) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);

  ASSERT_EQ(M1 == M2, true);
}
TEST(OPERATOR_EQUAL, EQ_3x3_3x3_2) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 10};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);

  ASSERT_EQ(M1 == M2, false);
}

TEST(OPERATOR_EQUATE, EQUATE1) {
  S21Matrix M1(3, 3);
  S21Matrix M2;
  S21Matrix M1_TEST(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  M1.fillMatrix(values_M1);
  M1_TEST.fillMatrix(values_M1);
  M2 = M1;

  ASSERT_EQ(M2.EqMatrix(M1_TEST), true);
  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
}
TEST(OPERATOR_EQUATE, EQUATE2) {
  S21Matrix M1(3, 3);
  S21Matrix M2(4, 4);
  S21Matrix M1_TEST(3, 3);
  S21Matrix M2_TEST(4, 4);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[16] = {1, 2,  3,  4,  5,  6,  7,  8,
                          9, 10, 11, 12, 13, 14, 15, 16};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M1_TEST.fillMatrix(values_M1);
  M2 = M1;

  ASSERT_EQ(M2.EqMatrix(M1_TEST), true);
  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
}
TEST(OPERATOR_EQUATE, EQUATE3) {
  S21Matrix M1(3, 3);
  S21Matrix M1_TEST(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  M1.fillMatrix(values_M1);
  M1_TEST.fillMatrix(values_M1);
  M1 = M1;

  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
}

TEST(OPERATOR_PLUS_EQUAL, PLUS_EQ_3x3_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix M2_TEST(3, 3);
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {2, 4, 6, 8, 10, 12, 14, 16, 18};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M2_TEST.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1 += M2;

  ASSERT_EQ(M1.EqMatrix(result), true);
  ASSERT_EQ(M2.EqMatrix(M2_TEST), true);
}

TEST(OPERATOR_MINUS_EQUAL, MINUS_EQ_3x3_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix M2_TEST(3, 3);
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {0};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M2_TEST.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1 -= M2;

  ASSERT_EQ(M1.EqMatrix(result), true);
  ASSERT_EQ(M2.EqMatrix(M2_TEST), true);
}

TEST(OPERATOR_MUL_MATRIX_EQUAL, MUL_EQ_3x3_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix M2_TEST(3, 3);
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_M2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {30, 36, 42, 66, 81, 96, 102, 126, 150};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M2_TEST.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1 *= M2;

  ASSERT_EQ(M1.EqMatrix(result), true);
  ASSERT_EQ(M2.EqMatrix(M2_TEST), true);
}

TEST(OPERATOR_MUL_NUMBER_EQUAL, MUL_EQ_3x3_3x3) {
  S21Matrix M1(3, 3);
  double number = 5;
  double number_test = number;
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {5, 10, 15, 20, 25, 30, 35, 40, 45};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M1 *= number;

  ASSERT_EQ(M1.EqMatrix(result), true);
  ASSERT_EQ(number, number_test);
}

TEST(OPERATOR_INDEX, INDEX_1x1) {
  S21Matrix M1(1, 1);
  double values_M1[1] = {1};

  M1.fillMatrix(values_M1);

  ASSERT_EQ(M1(0, 0), 1);
}
TEST(OPERATOR_INDEX, INDEX_2x2) {
  S21Matrix M1(2, 2);
  double values_M1[4] = {1, 2, 3, 4};

  M1.fillMatrix(values_M1);

  ASSERT_EQ(M1(0, 0), 1);
  ASSERT_EQ(M1(0, 1), 2);
  ASSERT_EQ(M1(1, 0), 3);
  ASSERT_EQ(M1(1, 1), 4);
}
TEST(OPERATOR_INDEX, INDEX_IS_OUT_OF_RANGE_2x2_1) {
  try {
    S21Matrix M1(2, 2);
    double values_M1[4] = {1, 2, 3, 4};

    M1.fillMatrix(values_M1);

    M1(-1, 0);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Index is out of range");
  }
}
TEST(OPERATOR_INDEX, INDEX_IS_OUT_OF_RANGE_2x2_2) {
  try {
    S21Matrix M1(2, 2);
    double values_M1[4] = {1, 2, 3, 4};

    M1.fillMatrix(values_M1);

    M1(0, -1);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Index is out of range");
  }
}
TEST(OPERATOR_INDEX, INDEX_IS_OUT_OF_RANGE_2x2_3) {
  try {
    S21Matrix M1(2, 2);
    double values_M1[4] = {1, 2, 3, 4};

    M1.fillMatrix(values_M1);

    M1(3, 0);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Index is out of range");
  }
}
