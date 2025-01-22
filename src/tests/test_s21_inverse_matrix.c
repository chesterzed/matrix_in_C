#include "tests.h"

START_TEST(test_1) {
  matrix_t A;
  int error = s21_inverse_matrix(NULL, &A);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_2) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);
  int error = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(error, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_3) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.0;
  int error = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(error, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_4) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  int error = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 1.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 1.5, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -0.5, EPS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_5) {
  matrix_t m1, m_r, m_ideal, m_mult;
  s21_create_matrix(3, 3, &m1);
  s21_create_matrix(3, 3, &m_ideal);
  m1.matrix[0][0] = 2;
  m1.matrix[0][1] = 5;
  m1.matrix[0][2] = 7;
  m1.matrix[1][0] = 6;
  m1.matrix[1][1] = 3;
  m1.matrix[1][2] = 4;
  m1.matrix[2][0] = 5;
  m1.matrix[2][1] = -2;
  m1.matrix[2][2] = -3;

  m_ideal.matrix[0][0] = 1;
  m_ideal.matrix[0][1] = -1;
  m_ideal.matrix[0][2] = 1;
  m_ideal.matrix[1][0] = -38;
  m_ideal.matrix[1][1] = 41;
  m_ideal.matrix[1][2] = -34;
  m_ideal.matrix[2][0] = 27;
  m_ideal.matrix[2][1] = -29;
  m_ideal.matrix[2][2] = 24;
  int res = s21_inverse_matrix(&m1, &m_r);
  int res2 = s21_mult_matrix(&m1, &m_r, &m_mult);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res2, 0);
  ck_assert_int_eq(s21_eq_matrix(&m_r, &m_ideal), 1);
  for (int i = 0; i < m_mult.rows; i++) {
    for (int j = 0; j < m_mult.columns; j++) {
      if (i == j) {
        ck_assert_double_eq(m_mult.matrix[i][j], 1);
      } else {
        ck_assert_double_eq(m_mult.matrix[i][j], 0);
      }
    }
  }

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m_r);
  s21_remove_matrix(&m_ideal);
  s21_remove_matrix(&m_mult);
}
END_TEST

START_TEST(test_6) {
  matrix_t m1, m_r, m_mult;
  s21_create_matrix(5, 5, &m1);
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = -1;
  m1.matrix[0][3] = 4;
  m1.matrix[0][4] = 6;

  m1.matrix[1][0] = -3;
  m1.matrix[1][1] = 5;
  m1.matrix[1][2] = 2;
  m1.matrix[1][3] = 0;
  m1.matrix[1][4] = -1;

  m1.matrix[2][0] = 1;
  m1.matrix[2][1] = 3;
  m1.matrix[2][2] = -2;
  m1.matrix[2][3] = 7;
  m1.matrix[2][4] = 9;

  m1.matrix[3][0] = 0;
  m1.matrix[3][1] = -4;
  m1.matrix[3][2] = 6;
  m1.matrix[3][3] = 8;
  m1.matrix[3][4] = -2;

  m1.matrix[4][0] = -7;
  m1.matrix[4][1] = 1;
  m1.matrix[4][2] = 3;
  m1.matrix[4][3] = -5;
  m1.matrix[4][4] = 4;

  int res = s21_inverse_matrix(&m1, &m_r);

  int res2 = s21_mult_matrix(&m1, &m_r, &m_mult);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res2, 0);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m_r);
  s21_remove_matrix(&m_mult);
}
END_TEST

Suite *make_s21_inverse_matrix_suite(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);

  suite_add_tcase(s, tc);
  return s;
}