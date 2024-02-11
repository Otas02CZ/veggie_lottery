//AUTHOR: Otakar Kočí
//DATE: 11/2/2024
//FILE: message.c
//DESCRIPTION: Source file for message.h

#include "message.h"

/**
 * @brief Destroys a Message object
 * 
 * @param message type MESSAGE* - pointer to the MESSAGE object
 * @note The function frees the memory allocated for the MESSAGE* object and its members
 */
void destroyMessage(MESSAGE* message) {
    if (message == NULL)
        return;
    if (message->text != NULL)
        free(message->text);
    free(message);
}

/**
 * @brief Creates and returns a Message object
 * 
 * @param text type char* - text of the message
 * @param isGood type bool - if the message is good or not (for pairing with veggies)
 * @note The function allocates memory for the MESSAGE* object and its members, the size of the allocated
 * memory of the member string is determined by the length of the input string
 * @return MESSAGE* pointer to the created MESSAGE object
 */
MESSAGE* createMessage(char* text, bool isGood) {
    MESSAGE* message = malloc(sizeof(MESSAGE));
    if (message == NULL)
        return NULL;
    if ((message->text = malloc((strlen(text)+1) * sizeof(char))) == NULL) {
        free(message);
        return NULL;
    }
    strcpy(message->text, text);
    message->isGood = isGood;
    return message;
}

/**
 * @brief Creates and returns a Message storage object
 * 
 * @param prealloc type __uint16_t - size of the storage to be preallocated
 * @note The function allocates memory for the MESSAGE_STORAGE* object and its members, the size of the allocated
 * memory of the member array is determined by the prealloc parameter and later is increased
 * by INCREMENT if used size would exceed the allocated size
 * @return MESSAGE_STORAGE* pointer to the created MESSAGE_STORAGE object
 */
MESSAGE_STORAGE* createMessageStorage(__uint16_t prealloc) {
    MESSAGE_STORAGE* storage = malloc(sizeof(MESSAGE_STORAGE));
    if (storage == NULL)
        return NULL;
    if ((storage->data = malloc(prealloc * sizeof(MESSAGE*))) == NULL) {
        free(storage);
        return NULL;
    }
    storage->used = 0;
    storage->allocated = prealloc;
    return storage;
}

/**
 * @brief Destroys a Message storage object and its members (all MESSAGE* objects in it)
 * 
 * @param storage type MESSAGE_STORAGE* - pointer to the MESSAGE_STORAGE object
 * @note The function frees the memory allocated for the MESSAGE_STORAGE* object and its members
 */
void deleteMessageStorage(MESSAGE_STORAGE* storage) {
    if (storage == NULL)
        return;
    for (__uint16_t i=0;i<storage->used;i++) {
        destroyMessage(storage->data[i]);
    }
    free(storage->data);
    free(storage);
}

/**
 * @brief Checks whether the used size would be exceeded and reallocates the memory if needed
 * and then creates and returns a Message object (using createMessage()) and adds it to the storage at the end
 * 
 * @param messageStorage type MESSAGE_STORAGE* - pointer to the MESSAGE_STORAGE object
 * the rest of the parameters are the same as in createMessage() and specify a new MESSAGE object
 * @param text type char* - text of the message
 * @param isGood type bool - if the message is good or not (for pairing with veggies)
 * @note The function adds a MESSAGE* object to the MESSAGE_STORAGE* object. If the used size would exceed the allocated size
 * ,the function reallocates the memory for the array of MESSAGE* objects with size increased by INCREMENT
 * @return MESSAGE* pointer to the added MESSAGE object
 */
MESSAGE* addMessageToStorage(MESSAGE_STORAGE* messageStorage, char* text, bool isGood) {
    if (messageStorage == NULL)
        return NULL;
    if (messageStorage->used == messageStorage->allocated) {
        if (messageStorage->allocated+INCREMENT >= __UINT16_MAX__)
            return NULL;
        MESSAGE** newMessages = realloc(messageStorage->data, (messageStorage->allocated + INCREMENT) * sizeof(MESSAGE*));
        if (newMessages == NULL)
            return NULL;
        messageStorage->data = newMessages;
        messageStorage->allocated += INCREMENT;
    }
    MESSAGE* message = createMessage(text, isGood);
    if (message == NULL)
        return NULL;
    messageStorage->data[messageStorage->used++] = message;
    return message;
}

/**
 * @brief Destroys a Message object in the storage and moves the rest of the objects to fill the gap (-1 if any)
 * 
 * @param storage type MESSAGE_STORAGE* - pointer to the MESSAGE_STORAGE object
 * @param index type __uint16_t - index of the message to be destroyed
 * @note The function frees the memory allocated for the MESSAGE* object and moves the rest of the objects
 * to fill the gap (-1 if any), the member used (used elements) is decremented by 1
 * @return bool true if the message was destroyed, false if the storage is NULL or the index is out of bounds
 */
bool destroyMessageInStorage(MESSAGE_STORAGE* messageStorage, __uint16_t index) {
    if (messageStorage == NULL || index >= messageStorage->used)
        return false;
    destroyMessage(messageStorage->data[index]);
    for (__uint16_t i=index;i<messageStorage->used-1;i++) {
        messageStorage->data[i] = messageStorage->data[i+1];
    }
    messageStorage->used--;
    return true;
}