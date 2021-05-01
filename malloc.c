/*
** EPITECH PROJECT, 2021
** B-PSU-400-STG-4-1-malloc-arthur.robine
** File description:
** Created by arthur,
*/

#include <stdlib.h>
#include "malloc.h"

void *heap_start = NULL;

void reduce_heap(alloc_data *block)
{
    size_t to_rm = 0;
    alloc_data *tmp = count_free(&to_rm, block);
    void *end = NULL;

    to_rm -= (to_rm % (getpagesize() * 2));
    if (tmp && tmp->free && to_rm > 0) {
        end = (void *)tmp + ALLOC_SIZE + tmp->size;
        while (tmp->prev && (void *)tmp >= end - to_rm)
            tmp = tmp->prev;
        tmp->size = (end - to_rm) - ((void *)tmp + ALLOC_SIZE);
        tmp->next = NULL;
        sbrk(-1 * (to_rm));
        if (heap_start == sbrk(0))
            heap_start = NULL;
    }
}

void add_block(alloc_data *new)
{
    alloc_data *tmp = heap_start;

    while (tmp && tmp->next)
        tmp = tmp->next;
    if (!tmp) {
        heap_start = new;
        new->prev = NULL;
    } else {
        new->prev = tmp;
        tmp->next = new;
    }
}

void *malloc(size_t size)
{
    alloc_data *buff = NULL;

    if (size < 1 || 16711568 < size)
        return NULL;
    if (heap_start == NULL && alloc(size)) {
        return ((alloc_data *)heap_start + 1);
    } else if (heap_start) {
        buff = recycle_blocks(heap_start, size);
        if (!buff) {
            buff = alloc(size);
            if (!buff)
                return NULL;
        }
    }
    return buff ? (buff + 1) : NULL;
}