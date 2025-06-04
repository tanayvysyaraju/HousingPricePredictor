#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transpose(double **matrix, double **result, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

void matrix_multiply(double **A, double **B, double **result, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void inverse(double **matrix, double **result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                result[i][j] = 1.0;
            } 
            else {
                result[i][j] = 0.0;
            }
        }
    }

    for (int p = 0; p < n; p++) {
        double pivot = matrix[p][p];
        for (int j = 0; j < n; j++) {
            matrix[p][j] = matrix[p][j] / pivot;
            result[p][j] = result[p][j] / pivot;
        }

        for (int i = p + 1; i < n; i++) {
            double factor = matrix[i][p];
            for (int j = 0; j < n; j++) {
                matrix[i][j] -= (factor * matrix[p][j]);
                result[i][j] -= (factor * result[p][j]);
            }
        }
    }

    for (int p = n - 1; p >= 0; p--) {
        for (int i = p - 1; i >= 0; i--) {
            double factor = matrix[i][p];
            for (int j = 0; j < n; j++) {
                matrix[i][j] -= (factor * matrix[p][j]);
                result[i][j] -= (factor * result[p][j]);
            }
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    FILE *train_file = fopen(argv[1], "r");
    FILE *data_file = fopen(argv[2], "r");

    char train_header[6];
    int r, c;
    fscanf(train_file, "%5s", train_header);
    fscanf(train_file, "%d", &c);
    fscanf(train_file, "%d", &r);

    double **X = (double **)malloc(r * sizeof(double *));
    double **Y = (double **)malloc(r * sizeof(double *));
    for (int i = 0; i < r; i++) {
        X[i] = (double *)malloc((c + 1) * sizeof(double));
        Y[i] = (double *)malloc(sizeof(double));
        X[i][0] = 1.0;
        for (int j = 1; j < c + 1; j++) {
            fscanf(train_file, "%lf", &X[i][j]);
        }
        fscanf(train_file, "%lf", &Y[i][0]);
    }  
    fclose(train_file);

    double **X_T = (double **)malloc((c + 1) * sizeof(double *));
    for (int i = 0; i < c + 1; i++) {
        X_T[i] = (double *)malloc(r * sizeof(double));
    }
    double **XTX = (double **)malloc((c + 1) * sizeof(double *));
    for (int i = 0; i < c + 1; i++) {
        XTX[i] = (double *)malloc((c + 1) * sizeof(double));
    }
    double **XTY = (double **)malloc((c + 1) * sizeof(double *));
    for (int i = 0; i < c + 1; i++) {
        XTY[i] = (double *)malloc(1 * sizeof(double));
    }
    double **W = (double **)malloc((c + 1) * sizeof(double *));
    for (int i = 0; i < c + 1; i++) {
        W[i] = (double *)malloc(1 * sizeof(double));
    }
    double **XTX_inv = (double **)malloc((c + 1) * sizeof(double *));
    for (int i = 0; i < c + 1; i++) {
        XTX_inv[i] = (double *)malloc((c + 1) * sizeof(double));
    }

    transpose(X, X_T, r, c + 1);
    matrix_multiply(X_T, X, XTX, c + 1, r, c + 1);
    inverse(XTX, XTX_inv, c + 1);
    for (int i = 0; i < c + 1; i++) {
        XTY[i][0] = 0.0;
        for (int j = 0; j < r; j++) {
            XTY[i][0] += X_T[i][j] * Y[j][0];
        }
    }

    for (int i = 0; i < c + 1; i++) {
        W[i][0] = 0.0;
        for (int j = 0; j < c + 1; j++) {
            W[i][0] += XTX_inv[i][j] * XTY[j][0];
        }
    }

    char data_header[5];
    int m, c_input;
    fscanf(data_file, "%4s", data_header);
    fscanf(data_file, "%d", &c_input);
    fscanf(data_file, "%d", &m);

    if (c != c_input) {
        fclose(data_file);
        return 1;
    }

    for (int i = 0; i < m; i++) {
        double *input = (double *)malloc((c + 1) * sizeof(double));
        input[0] = 1.0;
        for (int j = 1; j < c + 1; j++) {
            fscanf(data_file, "%lf", &input[j]);
        }

        double price = 0.0;
        for (int j = 0; j < c + 1; j++) {
            price += (W[j][0] * input[j]);
        }
        printf("%.0f\n", price);
        free(input);
    }

    fclose(data_file);

    for (int i = 0; i < r; i++) {
        free(X[i]);
        free(Y[i]);
    }
    for (int i = 0; i < c + 1; i++) {
        free(X_T[i]);
        free(XTX[i]);
        free(XTX_inv[i]);
        free(XTY[i]);
        free(W[i]);
    }
    free(X);
    free(Y);
    free(X_T);
    free(XTX);
    free(XTX_inv);
    free(XTY);
    free(W);
    return 0;
}