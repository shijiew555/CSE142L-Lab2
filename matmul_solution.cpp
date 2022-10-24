#include"cfiddle.hpp"
#include"matmul.hpp"
#include <fstream>
#include <iostream>
using namespace std;

// Compute the matrix product: c = a * b
// This is a reference implementation.  You don't need to modify it.
extern "C" void matrix_product(Matrix * c, Matrix * a, Matrix * b) {
    for(uint i = 0; i < a->rows; i++) {
        for(uint j = 0; j < b->columns; j++) {
        matrix_write(c, j, i, 0);
            for(uint k = 0; k < a->columns; k++) {
                matrix_write(c, j, i,
                         matrix_read(c, j, i) +
                            (matrix_read(a, k, i) *
                             matrix_read(b, j, k)));
            }
        }
    }
}

//            (m, c, r, v)
//c->data[i * c->columns + j] = 0;
// These are the functions you'll be modifying.   Right now, they all just call the reference
// implementation above, but when you are done, they should be specialized depending on how they
// are called by the go() function in the next cell.
extern "C" void matrix_product_1(register Matrix * c, register Matrix * a, register Matrix * b) {
    uint64_t * a_data = a->data;
    uint64_t * b_data = b->data;
    uint a_col = a->columns;
    uint b_col = b->columns;
    uint a_row = a->rows;
    //uint b_row = b->rows;
    
    for(register uint i = 0; i < a_row; i++) {
        for(register uint j = 0; j < b_col; j++) {
            register uint64_t rc_sum = 0;
            for(uint k = 0; k < a_col; k++) {
                rc_sum += a_data[i * a_col + k] * b_data[k * b_col + j];
            }
            matrix_write(c, j, i, rc_sum);
        }
    }
}

extern "C" void matrix_product_2(register Matrix * c, register Matrix * a, register Matrix * b) {
    uint64_t * a_data = a->data;
    uint64_t * b_data = b->data;
    uint a_col = a->columns;
    uint b_col = b->columns;
    uint a_row = a->rows;
    //uint b_row = b->rows;
    
    for(register uint i = 0; i < a_row; i++) {
        for(register uint j = 0; j < b_col; j++) {
            register uint64_t rc_sum = 0;
            register uint base_a_ptr = i * a_col;
            register uint base_b_ptr = j;
            for(uint k = 0; k < a_col; k++) {
                rc_sum += a_data[base_a_ptr] * b_data[base_b_ptr];
                base_a_ptr += 1;
                base_b_ptr += b_col;
            }
            matrix_write(c, j, i, rc_sum);
        }
    }
}

extern "C" void matrix_product_3(register Matrix * c, register Matrix * a, register Matrix * b) {
    uint64_t * a_data = a->data;
    uint64_t * b_data = b->data;
    uint a_col = a->columns;
    uint b_col = b->columns;
    uint a_row = a->rows;
    //uint b_row = b->rows;
    
    for(register uint i = 0; i < a_row; i++) {
        for(register uint j = 0; j < b_col; j++) {
            register uint64_t rc_sum = 0;
            for(uint k = 0; k < a_col; k++) {
                rc_sum += a_data[i * a_col + k] * b_data[k * b_col + j];
            }
            matrix_write(c, j, i, rc_sum);
        }
    }
}

extern "C" void matrix_product_4(register Matrix * c, register Matrix * a, register Matrix * b) {
    uint64_t * a_data = a->data;
    uint64_t * b_data = b->data;
    uint a_col = a->columns;
    uint b_col = b->columns;
    uint a_row = a->rows;
    //uint b_row = b->rows;
    
    for(register uint i = 0; i < a_row; i++) {
        for(register uint j = 0; j < b_col; j++) {
            register uint64_t rc_sum = 0;
            register uint base_a_ptr = i * a_col;
            register uint base_b_ptr = j;
            for(uint k = 0; k < a_col; k++) {
                rc_sum += a_data[base_a_ptr] * b_data[base_b_ptr];
                base_a_ptr += 1;
                base_b_ptr += b_col;
            }
            matrix_write(c, j, i, rc_sum);
        }
    }
}

extern "C" void matrix_product_5(register Matrix * c, register Matrix * a, register Matrix * b) {
    
}

// Cfiddle-signature=15f5bf8f5196d7b198b97125f46fbd11