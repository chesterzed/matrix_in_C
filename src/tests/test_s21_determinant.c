#include "tests.h"

START_TEST(test_1) {
  double result;
  int error = s21_determinant(NULL, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_2) {
  matrix_t mat = {.rows = -1, .columns = 4};
  double result;
  int error = s21_determinant(&mat, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_3) {
  matrix_t mat = {.rows = 2, .columns = 3};
  double result;
  int error = s21_determinant(&mat, &result);
  ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(test_4) {
  matrix_t mat = {.rows = 1, .columns = 1};
  mat.matrix = malloc(sizeof(double *));
  mat.matrix[0] = malloc(sizeof(double));
  mat.matrix[0][0] = 5.0;
  double result;
  int error = s21_determinant(&mat, &result);
  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(result, 5.0, 1e-6);
  // Здесь должен быть код освобождения памяти матрицы
  s21_remove_matrix(&mat);
}
END_TEST

Suite *make_s21_determinant_suite(void) {
  Suite *s = suite_create("s21_determinant");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);

  suite_add_tcase(s, tc);
  return s;
}
