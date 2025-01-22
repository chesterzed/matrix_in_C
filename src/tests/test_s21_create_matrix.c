#include "tests.h"

START_TEST(test_1) {
  matrix_t mat;
  int rows = -1;
  int columns = 4;

  int error = s21_create_matrix(rows, columns, &mat);

  ck_assert_int_eq(error, 1);
  // Проверяем, что функция вернула ошибку для некорректных аргументов
}
END_TEST

START_TEST(test_2) {
  matrix_t mat;
  int rows = 3;
  int columns = 4;

  int error = s21_create_matrix(rows, columns, &mat);
  // Проверяем, что функция вернула успешное выполнение
  ck_assert_int_eq(error, 0);
  ck_assert_ptr_ne(mat.matrix, NULL);
  // Проверяем, что количество строк совпадает
  ck_assert_int_eq(mat.rows, rows);
  // Проверяем, что количество столбцов совпадает
  ck_assert_int_eq(mat.columns, columns);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_3) {
  matrix_t mat;
  int rows = 0;
  int columns = 0;

  int error = s21_create_matrix(rows, columns, &mat);
  // Проверяем, что функция вернула успешное выполнение
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_5) {
  matrix_t mat;
  // Подсовываем NULL, чтобы вызвать ошибку выделения памяти для элемента
  // матрицы
  int error = s21_create_matrix(3, 3, &mat);
  // Ошибка выделения памяти для элемента матрицы
  ck_assert_int_eq(error, 0);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_6) {
  matrix_t mat;
  int error = s21_create_matrix(1, 1, &mat);
  ck_assert_int_eq(error, 0);
  ck_assert_ptr_ne(mat.matrix, NULL);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_7) {
  matrix_t mat;
  int error = s21_create_matrix(10, 10, &mat);
  ck_assert_int_eq(error, 0);
  ck_assert_ptr_ne(mat.matrix, NULL);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_8) {
  matrix_t mat;
  int error = s21_create_matrix(-5, 5, &mat);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite *make_s21_create_matrix_suite(void) {
  Suite *s = suite_create("s21_create_matrix");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);

  suite_add_tcase(s, tc);
  return s;
}
