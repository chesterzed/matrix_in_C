#include "tests.h"

START_TEST(test_1) {
  // Проверка на сравнение двух NULL матриц
  int result = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(result, FAILURE);  // Должно вернуть FAILURE для NULL матриц
}
END_TEST

START_TEST(test_2) {
  // Проверка на сравнение матриц разных размеров
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 3, &B);
  int result = s21_eq_matrix(&A, &B);
  // Должно вернуть FAILURE для матриц разных размеров
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_3) {
  // Проверка сравнения матриц, которые равны в пределах заданной погрешности
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  // Немного отличающиеся значения в пределах допустимой погрешности
  B.matrix[0][0] = 1.0 + EPS / 2;
  B.matrix[0][1] = 2.0 - EPS / 2;
  B.matrix[1][0] = 3.0 + EPS / 2;
  B.matrix[1][1] = 4.0 - EPS / 2;
  int result = s21_eq_matrix(&A, &B);
  // Должно вернуть SUCCESS для матриц, находящихся в пределах погрешности
  ck_assert_int_eq(result, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_4) {
  // Проверка сравнения матриц, которые не равны в пределах заданной погрешности
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  // Значения с разницей больше, чем допустимая погрешность
  B.matrix[0][0] = 1.1;
  B.matrix[0][1] = 1.9;
  B.matrix[1][0] = 3.1;
  B.matrix[1][1] = 4.1;
  int result = s21_eq_matrix(&A, &B);
  // Должно вернуть FAILURE для матриц, находящихся вне пределов погрешности
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *make_s21_eq_matrix_suite(void) {
  Suite *s = suite_create("s21_eq_matrix");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);

  suite_add_tcase(s, tc);
  return s;
}