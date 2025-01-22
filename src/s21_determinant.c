#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else if (A->rows != A->columns)
    error = 2;
  else {
    if (A->rows == 1)
      *result = A->matrix[0][0];
    else
      *result = s21_calc_determinant(A->rows, A);
  }
  return error;
}