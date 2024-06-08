#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#ifndef DYN_ARR
#define DYN_ARR

#define decl_dyn_arr_type(T) \
    typedef struct { \
        T *arr; \
        size_t len; \
        size_t cap; \
    } T##_dyn_arr_t; \
    T##_dyn_arr_t new_##T##_dyn_arr(size_t size) { \
        T *arr = malloc(sizeof(T) * size); \
        if (arr == NULL) { \
            perror("Error allocating dynamic array(new)\n"); \
            exit(1); \
        } \
        return (T##_dyn_arr_t){.arr = arr, .len = 0, .cap = size}; \
    } \
    void push_##T(T##_dyn_arr_t *dyn_arr, T el) { \
        dyn_arr->arr[dyn_arr->len++] = el; \
        if (dyn_arr->len == dyn_arr->cap) { \
            dyn_arr->cap *= 2; \
            dyn_arr->arr = realloc(dyn_arr->arr, sizeof(T) * dyn_arr->cap); \
            if (dyn_arr->arr == NULL) { \
                perror("Error reallocating dynamic array(push)\n"); \
                exit(1); \
            } \
        } \
    } \
    T pop_##T(T##_dyn_arr_t *dyn_arr) { \
        if (dyn_arr->len == 0) { \
            fprintf(stderr, "Trying to pop from empty dynamic array\n"); \
            exit(1); \
        } \
        T val = dyn_arr->arr[--dyn_arr->len]; \
        if (dyn_arr->len < dyn_arr->cap / 2) { \
            dyn_arr->cap /= 2; \
            dyn_arr->arr = realloc(dyn_arr->arr, sizeof(T) * dyn_arr->cap); \
            if (dyn_arr->arr == NULL) { \
                perror("Error reallocating dynamic array(pop)\n"); \
                exit(1); \
            } \
        } \
        return val; \
    } \
    T insert_##T##_at(T##_dyn_arr_t dyn_arr, size_t i, T el) { \
        if (i >= dyn_arr.len || i < 0) { \
            fprintf(stderr, "Dynamic array index out of bounds(insert_at): dyn_arr.len = %ld; i = %ld\n", dyn_arr.len, i); \
            exit(1); \
        } \
        return dyn_arr.arr[i] = el; \
    } \
    T T##_at(T##_dyn_arr_t dyn_arr, size_t i) { \
        if (i >= dyn_arr.len || i < 0) { \
            fprintf(stderr, "Dynamic array index out of bounds(at): dyn_arr.len = %ld; i = %ld\n", dyn_arr.len, i); \
            exit(1); \
        } \
        return dyn_arr.arr[i]; \
    } \
    void swap_##T(T##_dyn_arr_t dyn_arr, size_t i, size_t j) { \
        if (i >= dyn_arr.len || i < 0) { \
            fprintf(stderr, "Dynamic array index out of bounds(swap): dyn_arr.len = %ld; i = %ld\n", dyn_arr.len, i); \
            exit(1); \
        } \
        if (j >= dyn_arr.len || j < 0) { \
            fprintf(stderr, "Dynamic array index out of bounds(swap): dyn_arr.len = %ld; j = %ld\n", dyn_arr.len, j); \
            exit(1); \
        } \
        T tmp = dyn_arr.arr[i]; \
        dyn_arr.arr[i] = dyn_arr.arr[j]; \
        dyn_arr.arr[j] = tmp; \
    } \
    bool includes_##T(T##_dyn_arr_t dyn_arr, T el, bool (*same) (const T el1, const T el2)) { \
        bool incl = false; \
        for (size_t i = 0; i < dyn_arr.len; i++) { \
            if (same(el, dyn_arr.arr[i])) { \
                incl = true; \
                break; \
            } \
        } \
        return incl; \
    } \
    void clear_##T##_dyn_arr(T##_dyn_arr_t *dyn_arr) { \
        dyn_arr->len = 0; \
    } \
    void free_##T##_dyn_arr(T##_dyn_arr_t dyn_arr) { \
        free(dyn_arr.arr); \
    } \

#endif
