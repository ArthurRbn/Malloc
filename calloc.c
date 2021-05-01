/*
** EPITECH PROJECT, 2021
** B_PSU_400_STG_4_1_malloc_arthur_robine
** File description:
** Created by arthur,
*/

#include "malloc.h"

void *calloc(size_t nmemb, size_t size)
{
    size_t count = size * nmemb;
    void *block = NULL;

    block = malloc(count);
    if (block == NULL)
        return NULL;
    memset(block, 0, count);
    return block;
}