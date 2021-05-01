/*
** EPITECH PROJECT, 2021
** B_PSU_400_STG_4_1_malloc_arthur_robine
** File description:
** Created by arthur,
*/

#include "malloc.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t count = 0;
    size_t base_nmemb = nmemb;
    void *block = NULL;

    for (size_t i = 1; nmemb > 0 && (i * size + ALLOC_SIZE) < ULONG_MAX - size; --nmemb, ++i);
    count += size * (base_nmemb - nmemb);
    block = realloc(ptr, count);
    return block;
}