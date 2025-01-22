#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  double r;
  if (A == NULL || A->rows < 1 || A->columns < 1)
    error = 1;
  else if (A->rows != A->columns)
    error = 2;
  else if (!s21_determinant(A, &r) && !r)
    error = 2;
  else {
    matrix_t transpose, compl ;
    s21_calc_complements(A, &compl );
    s21_transpose(&compl, &transpose);
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = 1 / r * transpose.matrix[i][j];
    }
    s21_remove_matrix(&transpose);
    s21_remove_matrix(&compl );
  }

  return error;
}