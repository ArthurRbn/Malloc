/*
** EPITECH PROJECT, 2021
** B_PSU_400_STG_4_1_malloc_arthur_robine
** File description:
** Created by arthur,
*/

#include "malloc.h"

void merge_blocks(alloc_data *block)
{
    if (!block->next)
        return;
    block->size += block->next->size + ALLOC_SIZE;
    block->next = block->next->next;
    if (block->next)
        block->next->prev = block;
}

void split_block(alloc_data *block, size_t size)
{
    alloc_data *new = NULL;

    if (block->size == size)
        return;
    new = (void *)(block + 1) + size;
    new->size = block->size - size - ALLOC_SIZE;
    new->next = block->next;
    new->prev = block;
    new->free = true;
    block->next = new;
    block->size = size;
}

void *extend_to_next(alloc_data *block, size_t size)
{
    if (size % 2 != 0)
        size++;
    if (block->size > (size + ALLOC_SIZE)) {
        split_block(block, size);
        return (alloc_data *)block + 1;
    } else if (size < block->size && !(size < (block->size - ALLOC_SIZE))) {
        return (alloc_data *)block + 1;
    }
    if (!block->next || block->next->free == false) {
        return NULL;
    } else if ((size + ALLOC_SIZE - block->size) <= block->next->size) {
        merge_blocks(block);
        return ++block;
    }
    return NULL;
}

void *realloc(void *ptr, size_t size)
{
    alloc_data *block = NULL;
    alloc_data *base = ptr ? ptr - ALLOC_SIZE : NULL;

    if (!ptr) {
        return malloc(size);
    } else if (ptr && size < 1) {
        free(ptr);
    } else {
        block = extend_to_next(ptr - ALLOC_SIZE, size);
        if (!block) {
            block = malloc(size);
            if (!block || ptr == block)
                return ptr;
            memcpy(block, ptr, (base->size > ((alloc_data *)block - 1)->size) ? ((alloc_data *)block - 1)->size : base->size);
            free(ptr);
        }
    }
    return block;
}