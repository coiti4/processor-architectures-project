/**
 * @file matrix_ops.c
 * @brief Implementation of basic matrix operations with performance measurement.
 */

#include "matrix_ops.h"
#include "tsc.h"

TYPE AF[N][N], YF[N][N], XF[N][N], YT[N][N]; /**< Matrices of size [N][N] */
TYPE BF[N * N], CF[N * N];                  /**< Vectors of size N^2 */
TYPE SF;                                     /**< Scalar accumulator */
double results[M];                           /**< Array to store benchmark results in number of cycles*/

unsigned long long start_time;
double benchmark_time;

/**
 * @brief Computes the minimum of two integers.
 * 
 * @param a First integer.
 * @param b Second integer.
 * @return Minimum of a and b.
 */
static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

/**
 * @brief Stores a result in the results array.
 * 
 * @param res The result to store.
 * @param index The index where the result should be stored.
 */
void add_result(double res, int index) {
    results[index] = res;
}

/**
 * @brief Prints the benchmark results.
 * 
 * @param func_name Name of the function.
 * @param iterations Number of iterations for normalization.
 */
void print_results(const char *func_name, double iterations) {
    double normalize = 1.0 / iterations;
    printf("%s\t", func_name);
    for (int i = 0; i < M; i++) {
        printf("%.3f%s", results[i] * normalize, (i == M - 1 ? "\n" : "\t"));
    }
}

/**
 * @brief Separator for result output.
 */
void separator() {
    printf("\n");
}

/**
 * @brief Sets all elements of vector BF to zero.
 */
void zero_vector() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        for (int i = 0; i < (N * N); i++) {
            BF[i] = ZERO;
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("ZERO_VECTOR", (N * N));
    separator();
}

/**
 * @brief Copies matrix YF to AF in row-major order.
 */
void copy_matrix_ij() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                AF[i][j] = YF[i][j];
            }
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("COPY_MATRIX_IJ", (N * N));
    separator();
}

/**
 * @brief Copies matrix YF to AF in column-major order.
 */
void copy_matrix_ji() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                AF[i][j] = YF[i][j];
            }
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("COPY_MATRIX_JI", (N * N));
    separator();
}

/**
 * @brief Adds matrix YF to AF in row-major order.
 */
void add_matrix_ij() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                AF[i][j] += YF[i][j];
            }
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("ADD_MATRIX_IJ", (N * N));
    separator();
}

/**
 * @brief Adds matrix YF to AF in column-major order.
 */
void add_matrix_ji() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                AF[i][j] += YF[i][j];
            }
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("ADD_MATRIX_JI", (N * N));
    separator();
}

/**
 * @brief Computes the scalar product of vectors BF and CF.
 */
void scalar_product() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        SF = ZERO;
        for (int i = 0; i < (N * N); i++) {
            SF += BF[i] * CF[i];
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("SCALAR_PRODUCT", (N * N));
    separator();
}

/**
 * @brief Performs matrix multiplication AF * XF = YF in ijk order.
 */
void matrix_mult_ijk() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                SF = ZERO;
                for (int k = 0; k < N; k++) {
                    SF += AF[i][k] * XF[k][j];
                }
                YF[i][j] = SF;
            }
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("MATRIX_MULT_IJK", ((long long)N * N * N));
    separator();
}

/**
 * @brief Performs matrix multiplication AF * XF = YF in ikj order.
 */
void matrix_mult_ikj()
{
    int i, j, k, m;
    for (m = 0; m < M; m++) {
        start_time = start_timer();
        for (i = 0; i < N; i++) {
            for (k = 0; k < N; k++) {
                SF = AF[i][k];
                for (j = 0; j < N; j++) {
                    YF[i][j] += SF * XF[k][j];
                }
            }
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("MATRIX_MULT_IKJ", ((long long)N * N * N));
    separator();
}

/**
 * @brief Performs blocked matrix multiplication for optimized cache usage.
 */
void matrix_mult_blocked() {
    for (int m = 0; m < M; m++) {
        start_time = start_timer();
        for (int jj = 0; jj < N; jj += BL) {
            for (int kk = 0; kk < N; kk += BL) {
                for (int i = 0; i < N; i++) {
                    for (int j = jj; j < min(jj + BL, N); j++) {
                        SF = ZERO;
                        for (int k = kk; k < min(kk + BL, N); k++) {
                            SF += AF[i][k] * XF[k][j];
                        }
                        YF[i][j] = SF;
                    }
                }
            }
        }
        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }
    print_results("MATRIX_MULT_BLOCKED", ((long long)N * N * N));
    separator();
}

/**
 * @brief Matrix multiplication using the transposed matrix (i-j-k order).
 *
 * This function multiplies matrix A with the transposed matrix of X (XT) to improve cache efficiency.
 * The result is stored in matrix Y.
 */
void matrix_mult_trans_ijk() {
    int i, j, k, m;
    TYPE XT[N][N];  // Transposed matrix of X

    // Transpose the matrix X to improve memory access
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            XT[j][i] = XF[i][j];
        }
    }

    // Perform the matrix multiplication M times to measure performance
    for (m = 0; m < M; m++) {
        start_time = start_timer();
        
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                SF = ZERO;
                for (k = 0; k < N; k++) {
                    SF += AF[i][k] * XT[j][k];  // Use the transposed matrix XT
                }
                YF[i][j] = SF;
            }
        }

        benchmark_time = dtime(start_time, stop_timer());
        add_result(benchmark_time, m);
    }

    print_results("MM_TRANS_ijk", ((double)N * N * N));
    separator();
}
