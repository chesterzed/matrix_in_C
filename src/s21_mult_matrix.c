#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A == NULL || B == NULL || A->rows < 1 || B->rows < 1 || A->columns < 1 ||
      B->columns < 1)
    error = 1;
  else if (A->columns != B->rows)
    error = 2;
  else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0;
        for (int m = 0; m < A->columns; m++)
          result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
      }
    }
  }
  return error;
}