#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        matrix_t matrix_minor;
        s21_minor(i, j, A, &matrix_minor);
        double det_num = 0.0;
        s21_determinant(&matrix_minor, &det_num);
        result->matrix[i][j] = pow((-1), i + j) * det_num;
        s21_remove_matrix(&matrix_minor);
      }
    }
  }
  return error;
}