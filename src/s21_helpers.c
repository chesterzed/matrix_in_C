#include "s21_matrix.h"

void s21_minor(int n, int c, matrix_t *A, matrix_t *smat) {
  s21_create_matrix(A->rows - 1, A->columns - 1, smat);
  int i_n = 0;
  for (int i = 0; i < A->rows; i++) {
    int j_n = 0;
    if (i == n) continue;
    for (int j = 0; j < A->columns; j++) {
      if (j != c) {
        smat->matrix[i_n][j_n] = A->matrix[i][j];
        j_n++;
      }
    }
    i_n++;
  }
}

double s21_calc_determinant(int n, matrix_t *A) {
  matrix_t new_matrix;
  s21_create_matrix(A->rows - 1, A->columns - 1, &new_matrix);
  double result = 0;

  if (n == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    for (int i = 0; i < n; i++) {
      int numj = 0;
      for (int j = 1; j < n; j++) {
        int numk = 0;
        for (int k = 0; k < n; k++) {
          if (k != i) {
            new_matrix.matrix[numj][numk] = A->matrix[j][k];
            numk++;
          }
        }
        numj++;
      }
      result += pow(-1, i) * A->matrix[0][i] *
                s21_calc_determinant(n - 1, &new_matrix);
    }
  }
  s21_remove_matrix(&new_matrix);

  return result;
}
