//AUTHOR: Otakar Kočí
//DATE: 11/2/2024
//FILE: veggie.h
//DESCRIPTION: Header file for veggie.c

#ifndef VEGGIE_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define VEGGIE_H
#define INCREMENT 10 //INCREMENT for memory reallocation

/**
 * @brief Veggie structure for storing veggie data about veggies
 * @struct VEGGIE
 * @var VEGGIE::name type char* - name of the veggie
 * @var VEGGIE::article type char* - article of the veggie name
 * @var VEGGIE::isGood type bool - if the veggie is good or not (for later pairing with messages)
 */
typedef struct VEGGIE {
    char* name;
    char* article;
    bool isGood;
} VEGGIE;

/**
 * @brief Veggie storage structure for storing multiple veggies in a tight space
 * @struct VEGGIE_STORAGE
 * @var VEGGIE_STORAGE::veggies type VEGGIE** - array of pointers to VEGGIE structures
 * @var VEGGIE_STORAGE::used type __uint16_t - number of used elements in the array
 * @var VEGGIE_STORAGE::allocated type __uint16_t - number of allocated elements in the array
 * @note The array of pointers to VEGGIE structures is allocated dynamically (as needed when size is exceeded)
 * and its current size is determined by the allocated member
 */
typedef struct VEGGIE_STORAGE {
    VEGGIE** veggies;
    __uint16_t used;
    __uint16_t allocated;
} VEGGIE_STORAGE;

void destroyVeggie(VEGGIE* veggie);
VEGGIE* createVeggie(char* veggieName, char* article, bool isGood);
VEGGIE_STORAGE* createVeggieStorage(__uint16_t prealloc);
void deleteVeggieStorage(VEGGIE_STORAGE* veggieStorage);
VEGGIE* addVeggieToStorage(VEGGIE_STORAGE* veggieStorage, char* veggieName, char* article, bool isGood);
bool destroyVeggieInStorage(VEGGIE_STORAGE* veggieStorage, __uint16_t index);

#endif