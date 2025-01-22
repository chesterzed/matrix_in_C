#include "tests.h"

#include <stdio.h>
#include <stdlib.h>

#include "./../s21_matrix.h"

int main() {
  Suite *s_create_matrix = make_s21_create_matrix_suite();
  Suite *s_complements = make_s21_calc_complements_suite();
  Suite *s_transpose = make_s21_transpose_suite();
  Suite *s_sum_matrix = make_s21_sum_matrix_suite();
  Suite *s_sub_suite = make_s21_sub_matrix_suite();
  Suite *s_mult_number = make_s21_mult_number_suite();
  Suite *s_mult_matrix = make_s21_mult_matrix_suite();
  Suite *s_inverse_matrix = make_s21_inverse_matrix_suite();
  Suite *s_eq_matrix = make_s21_eq_matrix_suite();
  Suite *s_helpers = make_s21_helpers();
  Suite *s_determinant = make_s21_determinant_suite();

  SRunner *runner = srunner_create(s_create_matrix);
  srunner_add_suite(runner, s_complements);
  srunner_add_suite(runner, s_transpose);
  srunner_add_suite(runner, s_sum_matrix);
  srunner_add_suite(runner, s_sub_suite);
  srunner_add_suite(runner, s_mult_number);
  srunner_add_suite(runner, s_mult_matrix);
  srunner_add_suite(runner, s_inverse_matrix);
  srunner_add_suite(runner, s_eq_matrix);
  srunner_add_suite(runner, s_helpers);
  srunner_add_suite(runner, s_determinant);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
