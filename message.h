//AUTHOR: Otakar Kočí
//DATE: 11/2/2024
//FILE: message.h
//DESCRIPTION: Header file for message.c

#ifndef MESSAGE_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define MESSAGE_H
#define INCREMENT 10 //increment for memory reallocation

/**
 * @brief Message structure for storing message text and its goodness
 * @struct MESSAGE
 * @var MESSAGE::text type char* - message text
 * @var MESSAGE::isGood type bool - whether the message is good or not (for pairing with veggies)
 */
typedef struct MESSAGE {
    char* text;
    bool isGood;
} MESSAGE;

/**
 * @brief Message storage structure for storing multiple messages in a tight place
 * @struct MESSAGE_STORAGE
 * @var MESSAGE_STORAGE::data type MESSAGE** - array of pointers to MESSAGE structures
 * @var MESSAGE_STORAGE::allocated type unsigned short - number of allocated elements in the array
 * @var MESSAGE_STORAGE::used type unsigned short - number of used used elements in the array
 */
typedef struct MESSAGE_STORAGE {
    MESSAGE** data;
    unsigned short allocated;
    unsigned short used;
} MESSAGE_STORAGE;

void destroyMessage(MESSAGE* message);
MESSAGE* createMessage(char* text, bool isGood);
MESSAGE_STORAGE* createMessageStorage(unsigned short prealloc);
void deleteMessageStorage(MESSAGE_STORAGE* messageStorage);
MESSAGE* addMessageToStorage(MESSAGE_STORAGE* messageStorage, char* text, bool isGood);
bool destroyMessageInStorage(MESSAGE_STORAGE* messageStorage, unsigned short index);

#endif