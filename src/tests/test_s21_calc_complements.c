#include "tests.h"

START_TEST(test_1) {
  matrix_t A, result;
  int error = 0;

  // Создаем матрицу A для тестирования
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  // Вызываем функцию s21_calc_complements
  error = s21_calc_complements(&A, &result);

  // Проверяем, что функция завершилась без ошибок
  ck_assert_int_eq(error, 0);

  // Проверяем, что результат матрицы правильный
  ck_assert_int_eq(result.rows, A.rows);
  ck_assert_int_eq(result.columns, A.columns);
  ck_assert_double_eq_tol(result.matrix[0][0], -3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][1], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[0][2], -3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][0], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][1], -12.0, EPS);
  ck_assert_double_eq_tol(result.matrix[1][2], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][0], -3.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][1], 6.0, EPS);
  ck_assert_double_eq_tol(result.matrix[2][2], -3.0, EPS);

  // Очищаем выделенную память
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_2) {
  // Создаем матрицу A
  matrix_t A;
  A.columns = -2;
  A.rows = 3;
  matrix_t result;
  int error = s21_calc_complements(&A, &result);
  // Проверяем, что функция вернула код ошибки 0 (успех)
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite *make_s21_calc_complements_suite(void) {
  Suite *s = suite_create("s21_calc_complements");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);

  suite_add_tcase(s, tc);
  return s;
}
