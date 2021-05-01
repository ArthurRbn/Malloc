/*
** EPITECH PROJECT, 2021
** B-PSU-400-STG-4-1-malloc-arthur.robine
** File description:
** Created by arthur,
*/

#ifndef B_PSU_400_STG_4_1_MALLOC_ARTHUR_ROBINE_MALLOC_H
#define B_PSU_400_STG_4_1_MALLOC_ARTHUR_ROBINE_MALLOC_H

#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#define ALLOC_SIZE sizeof(alloc_data)

typedef struct alloc_data_s
{
    size_t size;
    bool free;
    struct alloc_data_s *next;
    struct alloc_data_s *prev;
} alloc_data;

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

void split_block(alloc_data *block, size_t size);
void reduce_heap(alloc_data *block);
void merge_blocks(alloc_data *block);
void *count_free(size_t *to_rm, alloc_data *block);
size_t align_mem(size_t *size);
void *alloc_to_block(alloc_data *block, size_t size);
alloc_data *recycle_blocks(alloc_data *list, size_t size);
alloc_data *alloc(size_t size);
void add_block(alloc_data *new);
size_t merge_align_mem(size_t *size, alloc_data *block);

#endif //B_PSU_400_STG_4_1_MALLOC_ARTHUR_ROBINE_MALLOC_H