#include "test_core.h"

TEST(EQ_MATRIX, EQ_MATRIX_2x2_ACCURACY7) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 2);
  double values_M1[4] = {1.1921650, 2, 3, 4};
  double values_M2[4] = {1.1921651, 2, 3, 4};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);

  ASSERT_EQ(M1.EqMatrix(M2), false);
}
TEST(EQ_MATRIX, EQ_MATRIX_2x2_ACCURACY8) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 2);
  double values_M1[4] = {1.19216501, 2, 3, 4};
  double values_M2[4] = {1.19216502, 2, 3, 4};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);

  ASSERT_EQ(M1.EqMatrix(M2), true);
}
TEST(EQ_MATRIX, EQ_MATRIX_1x1) {
  S21Matrix M1(1, 1);
  S21Matrix M2(1, 1);
  double values[1] = {1};

  M1.fillMatrix(values);
  M2.fillMatrix(values);

  ASSERT_EQ(M1.EqMatrix(M2), true);
}
TEST(EQ_MATRIX, EQ_MATRIX_2x2_2x3) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 3);
  double values_M1[4] = {1, 2, 3, 4};
  double values_M2[6] = {1, 2, 3, 4, 5, 6};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);

  ASSERT_EQ(M1.EqMatrix(M2), false);
}
TEST(EQ_MATRIX, EQ_MATRIX_2x2) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 3);
  S21Matrix M3(2, 2);
  double values_M1[4] = {1, 2, 3, 4};
  double values_M2[6] = {1, 2, 3, 4, 5, 6};
  double values_M3[4] = {1, 2, 4, 5};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  M3.fillMatrix(values_M3);
  M2.setCols(2);

  ASSERT_EQ(M2.EqMatrix(M3), true);
}
TEST(EQ_MATRIX, EQ_MATRIX_EMPTY) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 2);

  ASSERT_EQ(M1.EqMatrix(M2), true);
}
TEST(EQ_MATRIX, EQ_MATRIX_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;
    S21Matrix M2;

    M1.EqMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}

TEST(SUM_MATRIX, SUM_MATRIX_2x2) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 2);
  S21Matrix result(2, 2);
  double values_M1[4] = {121239.113, 2401.12392, -348901.2, 2389014};
  double values_M2[4] = {109428035910.10189, -19872409.1489, 3, 140912.5};
  double values_result[4] = {109428157149.21489, -19870008.02498, -348898.2,
                             2529926.5};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SumMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(SUM_MATRIX, SUM_MATRIX_1x1) {
  S21Matrix M1(1, 1);
  S21Matrix M2(1, 1);
  S21Matrix result(1, 1);
  double values_M1[1] = {38.12389};
  double values_M2[1] = {-129.4910};
  double values_result[1] = {-91.36711};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SumMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(SUM_MATRIX, SUM_MATRIX_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix result(3, 3);
  double values_M1[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                         912039.12389,  129034.23400, 0,         1203,
                         9000000.123};
  double values_M2[9] = {
      109428035910.1024189, -19872409.1489, 3, 140912.5, 0, 12930124, 1942.3489,
      102.234891,           10230912.1};
  double values_result[9] = {
      109428157149.2244319, -19870008.02498, -348898.2, 2529926.5,
      912039.12389,         13059158.234,    1942.3489, 1305.234891,
      19230912.223};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SumMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(SUM_MATRIX, SUM_MATRIX_2x2_2x1) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 1);

  try {
    M1.SumMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrices of unequal sizes");
  }
}
TEST(SUM_MATRIX, SUM_MATRIX_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;
    S21Matrix M2;

    M1.SumMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(SUB_MATRIX, SUM_MATRIX_2x3) {
  S21Matrix M1(2, 3);
  S21Matrix M2(2, 3);
  S21Matrix result(2, 3);
  double values_M1[6] = {1, 2, 3, 4, 5, 6};
  double values_M2[6] = {2, 3, 4, 5, 6, 7};
  double values_result[6] = {3, 5, 7, 9, 11, 13};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SumMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}

TEST(SUB_MATRIX, SUB_MATRIX_2x2) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 2);
  S21Matrix result(2, 2);
  double values_M1[4] = {121239.113, 2401.12392, -348901.2, 2389014};
  double values_M2[4] = {109910.10189, -19872409.1489, 3, 140912.5};
  double values_result[4] = {11329.01111, 19874810.27282, -348904.2, 2248101.5};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SubMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(SUB_MATRIX, SUB_MATRIX_1x1) {
  S21Matrix M1(1, 1);
  S21Matrix M2(1, 1);
  S21Matrix result(1, 1);
  double values_M1[1] = {38.12389};
  double values_M2[1] = {-129.4910};
  double values_result[1] = {167.61489};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SubMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(SUB_MATRIX, SUB_MATRIX_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix result(3, 3);
  double values_M1[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                         912039.12389,  129034.23400, 0,         1203,
                         9000000.123};
  double values_M2[9] = {
      109428035910.1024189, -19872409.1489, 3, 140912.5, 0, 12930124, 1942.3489,
      102.234891,           10230912.1};
  double values_result[9] = {
      -109427914670.9804059, 19874810.27282, -348904.2,  2248101.5,
      912039.12389,          -12801089.766,  -1942.3489, 1100.765109,
      -1230911.977};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SubMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(SUB_MATRIX, SUB_MATRIX_2x2_2x1) {
  S21Matrix M1(2, 2);
  S21Matrix M2(2, 1);

  try {
    M1.SubMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrices of unequal sizes");
  }
}
TEST(SUB_MATRIX, SUB_MATRIX_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;
    S21Matrix M2;

    M1.SubMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(SUB_MATRIX, SUB_MATRIX_2x3) {
  S21Matrix M1(2, 3);
  S21Matrix M2(2, 3);
  S21Matrix result(2, 3);
  double values_M1[6] = {1, 2, 3, 4, 5, 6};
  double values_M2[6] = {2, 3, 4, 5, 6, 7};
  double values_result[6] = {-1, -1, -1, -1, -1, -1};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.SubMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}

TEST(MUL_NUMBER, MUL_NUMBER_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;

    M1.MulNumber(10);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(MUL_NUMBER, MUL_NUMBER_1x1) {
  S21Matrix M1(1, 1);
  S21Matrix result(1, 1);
  double number = 10.2;
  double values_M1[1] = {105.3};
  double values_result[1] = {1074.06};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M1.MulNumber(number);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(MUL_NUMBER, MUL_NUMBER_2x2) {
  S21Matrix M1(2, 2);
  S21Matrix result(2, 2);
  double number = 3.12890;
  double values_M1[4] = {121239.113, 2401.12392, -348901.2, 2389014};
  double values_result[4] = {379345.0606657, 7512.876633288, -1091676.96468,
                             7474985.9046};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M1.MulNumber(number);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(MUL_NUMBER, MUL_NUMBER_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix result(3, 3);
  double number = 3901.904;
  double values_M1[9] = {121239.122013, 2401.12392,   -348901.2, 2389014,
                         912039.12389,  129034.23400, 0,         1203,
                         9000000.123};
  double values_result[9] = {473063415.139012752,
                             9368955.02794368,
                             -1361378987.8848,
                             9321703282.656,
                             3558689105.66288656,
                             503479193.781536,
                             0,
                             4693990.512,
                             35117136479.934192};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M1.MulNumber(number);

  ASSERT_EQ(M1.EqMatrix(result), true);
}

TEST(MUL_MATRIX, MUL_MATRIX_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;
    S21Matrix M2;

    M1.MulMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(MUL_MATRIX, MUL_MATRIX_INCORRECT) {
  try {
    S21Matrix M1(2, 3);
    S21Matrix M2(2, 3);

    M1.MulMatrix(M2);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "The matrices have unsuitable dimensions");
  }
}
TEST(MUL_MATRIX, MUL_MATRIX_2x3_3x2) {
  S21Matrix M1(2, 3);
  S21Matrix M2(3, 2);
  S21Matrix result(2, 2);
  double values_M1[6] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2};
  double values_M2[6] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0};
  double values_result[4] = {92.4, 117.6, 205.8, 268.8};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.MulMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(MUL_MATRIX, MUL_MATRIX_3x3_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2(3, 3);
  S21Matrix result(3, 3);
  double values_M1[9] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2, 8.4, 9.6, 10.8};
  double values_M2[9] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0, 24.5, 28.0, 31.5};
  double values_result[9] = {126,   151.2, 176.4, 277.2, 340.2,
                             403.2, 428.4, 529.2, 630};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.MulMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}
TEST(MUL_MATRIX, MUL_MATRIX_3x2_2x3) {
  S21Matrix M1(3, 2);
  S21Matrix M2(2, 3);
  S21Matrix result(3, 3);
  double values_M1[6] = {1.2, 2.4, 3.6, 4.8, 6.0, 7.2};
  double values_M2[6] = {3.5, 7.0, 10.5, 14.0, 17.5, 21.0};
  double values_result[9] = {37.8,  50.4,  63,  79.8, 109.2,
                             138.6, 121.8, 168, 214.2};

  M1.fillMatrix(values_M1);
  M2.fillMatrix(values_M2);
  result.fillMatrix(values_result);
  M1.MulMatrix(M2);

  ASSERT_EQ(M1.EqMatrix(result), true);
}

TEST(TRANSPOSE, TRANSPOSE_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;

    M1.Transpose();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(TRANSPOSE, TRANSPOSE_2x3) {
  S21Matrix M1(2, 3);
  S21Matrix M2;
  S21Matrix result(3, 2);
  double values_M1[6] = {1, 2, 3, 4, 5, 6};
  double values_result[6] = {1, 4, 2, 5, 3, 6};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.Transpose();

  ASSERT_EQ(M2.EqMatrix(result), true);
}
TEST(TRANSPOSE, TRANSPOSE_3x2) {
  S21Matrix M1(3, 2);
  S21Matrix M2;
  S21Matrix result(2, 3);
  double values_M1[6] = {1, 2, 3, 4, 5, 6};
  double values_result[6] = {1, 3, 5, 2, 4, 6};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.Transpose();

  ASSERT_EQ(M2.EqMatrix(result), true);
}
TEST(TRANSPOSE, TRANSPOSE_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2;
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double values_result[9] = {1, 4, 7, 2, 5, 8, 3, 6, 9};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.Transpose();

  ASSERT_EQ(M2.EqMatrix(result), true);
}

TEST(CALC_COMPLEMENTS, CALC_COMPLEMENTS_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;

    M1.CalcComplements();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(CALC_COMPLEMENTS, CALC_COMPLEMENTS_NOT_SQUARE) {
  try {
    S21Matrix M1(2, 1);

    M1.CalcComplements();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "The matrix is not square");
  }
}
TEST(CALC_COMPLEMENTS, CALC_COMPLEMENTS_1x1) {
  S21Matrix M1(1, 1);
  S21Matrix M2;
  S21Matrix result(1, 1);
  double values_M1[1] = {984.1238};
  double values_result[1] = {984.1238};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.CalcComplements();

  ASSERT_EQ(M2.EqMatrix(result), true);
}
TEST(CALC_COMPLEMENTS, CALC_COMPLEMENTS_2x2) {  // надо придумать
  S21Matrix M1(2, 2);
  S21Matrix M2;
  S21Matrix result(2, 2);
  double values_M1[4] = {28, 35, -40, 4};
  double values_result[4] = {4, 40, -35, 28};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.CalcComplements();

  ASSERT_EQ(M2.EqMatrix(result), true);
}
TEST(CALC_COMPLEMENTS, CALC_COMPLEMENTS_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2;
  S21Matrix result(3, 3);
  double values_M1[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double values_result[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.CalcComplements();

  ASSERT_EQ(M2.EqMatrix(result), true);
}

TEST(DETERMINANT, DETERMINANT_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;

    M1.Determinant();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(DETERMINANT, DETERMINANT_NOT_SQUARE) {
  try {
    S21Matrix M1(2, 1);

    M1.Determinant();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "The matrix is not square");
  }
}
TEST(DETERMINANT, DETERMINANT_1x1) {
  S21Matrix M1(1, 1);
  double values_M1[1] = {984.1238};

  M1.fillMatrix(values_M1);
  double det = M1.Determinant();

  ASSERT_EQ(det, 984.1238);
}
TEST(DETERMINANT, DETERMINANT_2x2) {
  S21Matrix M1(2, 2);
  double values_M1[4] = {9, 2, 96, 1931};

  M1.fillMatrix(values_M1);
  double det = M1.Determinant();
  ASSERT_EQ(det, 17187);
}
TEST(DETERMINANT, DETERMINANT_3x3) {
  S21Matrix M1(3, 3);
  double values_M1[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};

  M1.fillMatrix(values_M1);
  double det = M1.Determinant();

  ASSERT_EQ(det, -40);
}
TEST(DETERMINANT, DETERMINANT_5x5) {
  S21Matrix M1(5, 5);
  double values_M1[25] = {1,  2,  3,   4, 5,  6,  7,  8,  9,  10, 11, 12, 49,
                          14, 15, 161, 7, 18, 19, 20, 64, 48, 1,  2,  3};

  M1.fillMatrix(values_M1);
  double det = M1.Determinant();

  ASSERT_EQ(det, -1369800);
}

TEST(INVERSE_MATRIX, INVERSE_MATRIX_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;

    M1.InverseMatrix();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}
TEST(INVERSE_MATRIX, INVERSE_MATRIX_NOT_SQUARE) {
  try {
    S21Matrix M1(2, 1);

    M1.InverseMatrix();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "The matrix is not square");
  }
}
TEST(INVERSE_MATRIX, INVERSE_MATRIX_1x1) {
  S21Matrix M1(1, 1);
  S21Matrix M2;
  S21Matrix result(1, 1);
  double values_M1[1] = {42.12849};
  double values_result[1] = {1 / 42.12849};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.InverseMatrix();

  ASSERT_EQ(M2.EqMatrix(result), true);
}
TEST(INVERSE_MATRIX, INVERSE_MATRIX_2x2) {
  S21Matrix M1(2, 2);
  S21Matrix M2;
  S21Matrix result(2, 2);
  double values_M1[4] = {10, 30, 20, 10};
  double values_result[4] = {-0.02, 0.06, 0.04, -0.02};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.InverseMatrix();

  ASSERT_EQ(M2.EqMatrix(result), true);
}
TEST(INVERSE_MATRIX, INVERSE_MATRIX_3x3) {
  S21Matrix M1(3, 3);
  S21Matrix M2;
  S21Matrix result(3, 3);
  double values_M1[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double values_result[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};

  M1.fillMatrix(values_M1);
  result.fillMatrix(values_result);
  M2 = M1.InverseMatrix();

  ASSERT_EQ(M2.EqMatrix(result), true);
}
TEST(INVERSE_MATRIX, INVERSE_MATRIX_5x5) {
  try {
    S21Matrix M1(5, 5);
    double values_M1[25] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

    M1.fillMatrix(values_M1);
    M1.InverseMatrix();
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "The determinant is 0");
  }
}
