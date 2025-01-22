#include "tests.h"

START_TEST(test_1) {
  // Создаем и заполняем матрицу A
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i * 3 + j;
    }
  }

  // Вызываем функцию transpose для матрицы A
  matrix_t result;
  int error = s21_transpose(&A, &result);

  // Проверяем, что функция вернула успешный результат
  ck_assert_int_eq(error, 0);

  // Проверяем, что размеры результирующей матрицы правильные
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  // Проверяем, что элементы результирующей матрицы соответствуют
  // транспонированным элементам матрицы A
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], A.matrix[j][i]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_2) {
  // Подсовываем некорректные данные, чтобы вызвать ошибку
  matrix_t A;
  s21_create_matrix(3, 4, &A);
  A.rows = -3;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i * 2 + j;
    }
  }
  matrix_t result;
  int error = s21_transpose(&A, &result);

  // Проверяем, что функция вернула ошибку
  ck_assert_int_eq(error, 1);

  // Освобождаем ресурсы
  s21_remove_matrix(&A);
}
END_TEST

Suite *make_s21_transpose_suite(void) {
  Suite *s = suite_create("s21_transpose");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);

  suite_add_tcase(s, tc);
  return s;
}
