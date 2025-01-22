#include "tests.h"

START_TEST(test_1) {
  // Создаем матрицу A
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  // Создаем матрицу B
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 2.0;
  B.matrix[0][1] = 0.0;
  B.matrix[1][0] = 1.0;
  B.matrix[1][1] = 2.0;

  // Создаем матрицу result для сохранения результата
  matrix_t result;

  // Умножаем матрицу A на матрицу B
  int error = s21_mult_matrix(&A, &B, &result);

  // Проверяем, что функция вернула код ошибки 0 (успех)
  ck_assert_int_eq(error, 0);

  // Проверяем, что размеры результирующей матрицы соответствуют ожиданиям
  ck_assert_int_eq(result.rows, A.rows);
  ck_assert_int_eq(result.columns, B.columns);

  // Проверяем значения в результирующей матрице result
  ck_assert_double_eq(result.matrix[0][0], 4.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 10.0);
  ck_assert_double_eq(result.matrix[1][1], 8.0);

  // Освобождаем выделенную память для матриц
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_2) {
  // Создаем две матрицы A и B
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);

  // Заполняем матрицы A и B значениями
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 4.0;
  A.matrix[2][1] = 4.0;
  A.matrix[2][2] = 4.0;

  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 1.5;
  B.matrix[1][0] = 2.5;
  B.matrix[1][1] = 3.5;

  matrix_t result;

  int error = s21_mult_matrix(&A, &B, &result);

  // Проверяем, что функция вернула код ошибки 2
  ck_assert_int_eq(error, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_3) {
  // Создаем две матрицы A и B
  matrix_t A, B;
  A.columns = -2;
  A.rows = 5;

  s21_create_matrix(2, 2, &B);

  // Создаем матрицу result для сохранения результата
  matrix_t result;

  // Вызываем функцию s21_sub_matrix для вычитания матрицы B из матрицы A
  int error = s21_mult_matrix(&A, &B, &result);

  // Проверяем, что функция вернула код ошибки 1
  ck_assert_int_eq(error, 1);
  s21_remove_matrix(&B);
}
END_TEST

Suite *make_s21_mult_matrix_suite(void) {
  Suite *s = suite_create("s21_mult_matrix");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}
