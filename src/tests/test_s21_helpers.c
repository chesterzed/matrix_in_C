#include "tests.h"

START_TEST(test_1) {
  // Проверка вычисления определителя для 2x2 матрицы
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  double result = s21_calc_determinant(2, &A);
  ck_assert_double_eq(result, -2.0);  // Определитель 2x2 матрицы равен -2
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_2) {
  // Проверка вычисления определителя для 3x3 матрицы
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;
  double result = s21_calc_determinant(3, &A);
  ck_assert_double_eq(result, 0.0);  // Определитель 3x3 матрицы равен 0
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_3) {
  // Проверка вычисления определителя для 4x4 матрицы
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  // Заполнение матрицы значениями, чтобы убедиться в правильности результата
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 4.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 6.0;
  A.matrix[1][2] = 7.0;
  A.matrix[1][3] = 8.0;
  A.matrix[2][0] = 9.0;
  A.matrix[2][1] = 10.0;
  A.matrix[2][2] = 11.0;
  A.matrix[2][3] = 12.0;
  A.matrix[3][0] = 13.0;
  A.matrix[3][1] = 14.0;
  A.matrix[3][2] = 15.0;
  A.matrix[3][3] = 16.0;
  double result = s21_calc_determinant(4, &A);
  ck_assert_double_eq(result, 0.0);  // Определитель 4x4 матрицы равен 0
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_4) {
  // Проверка вычисления определителя для 5x5 матрицы
  matrix_t A;
  s21_create_matrix(5, 5, &A);
  // Заполнение матрицы значениями, чтобы убедиться в правильности результата
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 4.0;
  A.matrix[0][4] = 5.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 7.0;
  A.matrix[1][2] = 8.0;
  A.matrix[1][3] = 9.0;
  A.matrix[1][4] = 10.0;
  A.matrix[2][0] = 11.0;
  A.matrix[2][1] = 12.0;
  A.matrix[2][2] = 13.0;
  A.matrix[2][3] = 14.0;
  A.matrix[2][4] = 15.0;
  A.matrix[3][0] = 16.0;
  A.matrix[3][1] = 17.0;
  A.matrix[3][2] = 18.0;
  A.matrix[3][3] = 19.0;
  A.matrix[3][4] = 20.0;
  A.matrix[4][0] = 21.0;
  A.matrix[4][1] = 22.0;
  A.matrix[4][2] = 23.0;
  A.matrix[4][3] = 24.0;
  A.matrix[4][4] = 25.0;
  double result = s21_calc_determinant(5, &A);
  ck_assert_double_eq(result, 0.0);  // Определитель 5x5 матрицы равен 0
  s21_remove_matrix(&A);
}
END_TEST

Suite *make_s21_helpers(void) {
  Suite *s = suite_create("s21_helpers");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);

  suite_add_tcase(s, tc);
  return s;
}