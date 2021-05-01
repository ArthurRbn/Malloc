/*
** EPITECH PROJECT, 2021
** B_PSU_400_STG_4_1_malloc_arthur_robine
** File description:
** Created by arthur,
*/

#include "malloc.h"

size_t align_mem(size_t *size)
{
    size_t goal = 2 * getpagesize();
    size_t to_alloc = 0;

    if (*size % 2 != 0)
        (*size)++;
    to_alloc = goal - ((*size + ALLOC_SIZE) % goal);
    return to_alloc;
}

alloc_data *recycle_blocks(alloc_data *list, size_t size)
{
    alloc_data *tmp = list;

    for (; tmp && !(tmp->free == true && tmp->size >= size); tmp = tmp->next);
    if (tmp) {
        tmp->free = false;
        if (size > (tmp->size + ALLOC_SIZE)) {
            size = (size % 2 != 0) ? size + 1 : size;
            split_block(tmp, size);
        }
    }
    return tmp;
}

alloc_data *add_free_block(alloc_data *block, size_t to_goal, size_t size)
{
    alloc_data *free_block = NULL;

    free_block = (void *)block + ALLOC_SIZE + size;
    free_block->size = to_goal - ALLOC_SIZE;
    free_block->next = NULL;
    free_block->prev = block;
    free_block->free = true;
    return free_block;
}

alloc_data *alloc(size_t size)
{
    alloc_data *block = sbrk(0);
    alloc_data *free_block = NULL;
    size_t to_goal = align_mem(&size);
    void *alloc = sbrk(size + ALLOC_SIZE + to_goal);

    if (alloc == (void*) -1) {
        return NULL;
    } else if ((void *)block == alloc) {
        block->size = size + to_goal;
        if (to_goal > ALLOC_SIZE) {
            free_block = add_free_block(block, to_goal, size);
            block->size = size;
        }
        block->next = free_block;
        block->free = false;
        add_block(block);
    }
    return block;
}