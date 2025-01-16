/**
 * @file matrix_ops.h
 * @brief Header file for matrix operations with performance measurement.
 */

#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdio.h>
#include <stdint.h>

#ifndef N
#define N 1000 /**< Size of matrices [N][N] and vectors [N^2] */
#endif

#ifndef M
#define M 16 /**< Number of iterations for each function */
#endif

#ifndef TYPE
#define TYPE float /**< Data type for matrices and vectors (e.g., float, double, int) */
#endif

/**
 * @brief Define ZERO based on TYPE to avoid unnecessary type conversions.
 */
#if TYPE == int || TYPE == short || TYPE == char || TYPE == uint64_t
    #define ZERO 0
#elif TYPE == float
    #define ZERO 0.0f
#else
    #define ZERO 0.0
#endif

#ifndef BL
#define BL 16 /**< Block size for blocked matrix multiplication */
#endif

#define STR1(x) #x
#define STR(x) STR1(x)

/**
 * @brief Sets all elements of vector BF to zero.
 */
void zero_vector();

/**
 * @brief Copies matrix YF to AF in row-major order.
 */
void copy_matrix_ij();

/**
 * @brief Copies matrix YF to AF in column-major order.
 */
void copy_matrix_ji();

/**
 * @brief Adds matrix YF to AF in row-major order.
 */
void add_matrix_ij();

/**
 * @brief Adds matrix YF to AF in column-major order.
 */
void add_matrix_ji();

/**
 * @brief Computes the scalar product of vectors BF and CF.
 */
void scalar_product();

/**
 * @brief Performs matrix multiplication AF * XF = YF in ijk order.
 */
void matrix_mult_ijk();

/**
 * @brief Performs matrix multiplication AF * XF = YF in ikj order.
 */
void matrix_mult_ikj();

/**
 * @brief Performs blocked matrix multiplication for optimized cache usage.
 */
void matrix_mult_blocked();

#endif /* MATRIX_OPS_H */
