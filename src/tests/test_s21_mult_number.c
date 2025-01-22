#include "tests.h"

START_TEST(test_1) {
  // Создаем матрицу A
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  // Заполняем матрицу A значениями
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  // Создаем матрицу result для сохранения результата
  matrix_t result;

  // Умножаем матрицу A на число 2.0
  int error = s21_mult_number(&A, 2.0, &result);

  // Проверяем, что функция вернула код ошибки 0 (успех)
  ck_assert_int_eq(error, 0);

  // Проверяем, что размеры матрицы result соответствуют размерам A
  ck_assert_int_eq(result.rows, A.rows);
  ck_assert_int_eq(result.columns, A.columns);

  // Проверяем значения в результирующей матрице result
  ck_assert_double_eq(result.matrix[0][0], 2.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 6.0);
  ck_assert_double_eq(result.matrix[1][1], 8.0);

  // Освобождаем выделенную память для матриц
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_2) {
  // Создаем матрицу A
  matrix_t A;
  A.columns = -2;
  A.rows = 5;

  matrix_t result;

  int error = s21_mult_number(&A, 2.0, &result);

  // Проверяем, что функция вернула код ошибки 0 (успех)
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite *make_s21_mult_number_suite(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);

  suite_add_tcase(s, tc);
  return s;
}