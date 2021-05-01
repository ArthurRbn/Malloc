/*
** EPITECH PROJECT, 2021
** B_PSU_400_STG_4_1_malloc_arthur_robine
** File description:
** Created by arthur,
*/

#include "malloc.h"

void *count_free(size_t *to_rm, alloc_data *block)
{
    alloc_data *tmp = block;

    while (tmp->prev && tmp->prev->free) {
        tmp = tmp->prev;
    }
    while (tmp && tmp->next && tmp->free) {
        *to_rm += tmp->size + ALLOC_SIZE;
        tmp = tmp->next;
    }
    if (tmp && tmp->free)
        *to_rm += tmp->size + ALLOC_SIZE;
    return tmp;
}

void free(void *ptr)
{
    alloc_data *block = NULL;

    if (ptr == NULL)
        return;
    block = (alloc_data *)ptr - 1;
    if (block->free) {
        fprintf(stderr, "Error: unallocating free block at %p\n", ptr);
        _exit(84);
    } else {
        block->free = true;
        if (block->next && block->next->free) {
            merge_blocks(block);
        }
        if (block->prev && block->prev->free) {
            block = block->prev;
            merge_blocks(block);
        }
        reduce_heap(block);
    }
}