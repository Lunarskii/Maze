#include "test_core.h"

TEST(CONSTRUCTORS, COPY_CONSTRUCTOR_2x2) {
  S21Matrix M1(2, 2);
  S21Matrix M1_TEST(2, 2);
  double values_M1[4] = {1, 2, 3, 4};

  M1.fillMatrix(values_M1);
  M1_TEST.fillMatrix(values_M1);
  S21Matrix M2(M1);

  ASSERT_EQ(M1.EqMatrix(M1_TEST), true);
  ASSERT_EQ(M2.EqMatrix(M1_TEST), true);
}
TEST(CONSTRUCTORS, COPY_CONSTRUCTOR_DEFAULT_CONSTRUCTOR) {
  try {
    S21Matrix M1;
    S21Matrix M2(M1);
  } catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "Matrix size is invalid");
  }
}

TEST(CONSTRUCTORS, MOVE_CONSTRUCTOR) {
  S21Matrix M1(2, 2);
  double values_M1[4] = {1, 2, 3, 4};

  M1.fillMatrix(values_M1);
  S21Matrix M2(M1);
  S21Matrix M3(std::move(M1));

  ASSERT_EQ(M3.EqMatrix(M2), true);
  ASSERT_EQ(M1.getRows(), 0);
  ASSERT_EQ(M1.getCols(), 0);
}
