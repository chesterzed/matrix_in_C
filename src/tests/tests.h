#ifndef _UNI_TEST_H
#define _UNI_TEST_H
#include <check.h>
#include <math.h>

#include "../s21_matrix.h"

Suite *make_s21_create_matrix_suite(void);
Suite *make_s21_calc_complements_suite(void);
Suite *make_s21_transpose_suite(void);
Suite *make_s21_sum_matrix_suite(void);
Suite *make_s21_sub_matrix_suite(void);
Suite *make_s21_mult_number_suite(void);
Suite *make_s21_mult_matrix_suite(void);
Suite *make_s21_inverse_matrix_suite(void);
Suite *make_s21_eq_matrix_suite(void);
Suite *make_s21_helpers(void);
Suite *make_s21_determinant_suite(void);

#endif
