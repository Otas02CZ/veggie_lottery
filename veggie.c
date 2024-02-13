//AUTHOR: Otakar Kočí
//DATE: 11/2/2024
//FILE: veggie.c
//DESCRIPTION: Source file for veggie.h

#include "veggie.h"

/**
 * @brief Creates and returns a Veggie object
 * 
 * @param veggieName type char* - name of the veggie
 * @param article type char* - article of the veggie name
 * @param isGood type bool - if the veggie is good or not (for later pairing with messages)
 * @note The function allocates memory for the VEGGIE* object and its members, the size of the allocated
 * memory of the member strings is determined by the length of the input strings
 * @return VEGGIE* pointer to the created VEGGIE object
 */
VEGGIE* createVeggie(char* veggieName, char* article, bool isGood) {
    VEGGIE* veggie = malloc(sizeof(VEGGIE));
    if (veggie == NULL)
        return NULL;
    if ((veggie->article = malloc((strlen(article)+1) * sizeof(char))) == NULL)
        return NULL;
    if ((veggie->name = malloc((strlen(veggieName)+1) * sizeof(char))) == NULL) {
        free(veggie->article);
        return NULL;
    }
    strcpy(veggie->article, article);
    strcpy(veggie->name, veggieName);
    veggie->isGood = isGood;
    return veggie;
}

/**
 * @brief Destroys a Veggie object
 * 
 * @param veggie type VEGGIE* - pointer to the VEGGIE object
 * @note The function frees the memory allocated for the VEGGIE* object and its members
 */
void destroyVeggie(VEGGIE* veggie) {
    if (veggie == NULL)
        return;
    if (veggie->article != NULL)
        free(veggie->article);
    if (veggie->name != NULL)
        free(veggie->name);
    free(veggie);
}

/**
 * @brief Creates and returns a Veggie storage object
 * 
 * @param prealloc type unsigned short - size of the storage to be preallocated
 * @note The function allocates memory for the VEGGIE_STORAGE* object and its members, the size of the allocated
 * memory of the member array is determined by the prealloc parameter and later is increased
 * by INCREMENT if used size would exceed the allocated size
 * @return VEGGIE_STORAGE* pointer to the created VEGGIE_STORAGE object
 */
VEGGIE_STORAGE* createVeggieStorage(unsigned short prealloc) {
    VEGGIE_STORAGE* storage = malloc(sizeof(VEGGIE_STORAGE));
    if (storage == NULL)
        return NULL;
    if ((storage->data = malloc(prealloc * sizeof(VEGGIE*))) == NULL) {
        free(storage);
        return NULL;
    }
    storage->used = 0;
    storage->allocated = prealloc;
    return storage;
}

/**
 * @brief Destroys a Veggie storage object and its members (all VEGGIE* objects in it)
 * 
 * @param storage type VEGGIE_STORAGE* - pointer to the VEGGIE_STORAGE object
 * @note The function frees the memory allocated for the VEGGIE_STORAGE* object and its members
 */
void deleteVeggieStorage(VEGGIE_STORAGE* storage) {
    if (storage == NULL)
        return;
    for (unsigned short i=0;i<storage->used;i++) {
        destroyVeggie(storage->data[i]);
    }
    free(storage->data);
    free(storage);
}

/**
 * @brief Checks whether the used size would be exceeded and reallocates the memory if needed
 * and then creates and returns a Veggie object (using createVeggie()) and adds it to the storage at the end
 * 
 * @param storage type VEGGIE_STORAGE* - pointer to the VEGGIE_STORAGE object
 * the rest of the parameters are the same as in createVeggie() and specify a new veggie object
 * @param veggieName type char* - name of the veggie
 * @param article type char* - article of the veggie name
 * @param isGood type bool - if the veggie is good or not (for later pairing with messages)
 * @note The function adds a VEGGIE* object to the VEGGIE_STORAGE* object. If the used size would exceed the allocated size
 * ,the function reallocates the memory for the array of VEGGIE* objects with size increased by INCREMENT
 * @return VEGGIE* pointer to the created VEGGIE object
 */
VEGGIE* addVeggieToStorage(VEGGIE_STORAGE* storage, char* veggieName, char* article, bool isGood) {
    if (storage == NULL)
        return NULL;
    if (storage->used == storage->allocated) {
        if (storage->allocated+INCREMENT >= USHRT_MAX)
            return NULL;
        VEGGIE** newVeggies = realloc(storage->data, (storage->allocated + INCREMENT) * sizeof(VEGGIE*));
        if (newVeggies == NULL)
            return NULL;
        storage->data = newVeggies;
        storage->allocated += INCREMENT;
    }
    VEGGIE* veggie = createVeggie(veggieName, article, isGood);
    if (veggie == NULL)
        return NULL;
    storage->data[storage->used++] = veggie;
    return veggie;
}

/**
 * @brief Destroys a Veggie object in the storage and moves the rest of the objects to fill the gap (-1 if any)
 * 
 * @param storage type VEGGIE_STORAGE* - pointer to the VEGGIE_STORAGE object
 * @param index type unsigned short - index of the veggie to be destroyed
 * @note The function frees the memory allocated for the VEGGIE* object and moves the rest of the objects
 * to fill the gap (-1 if any), the member used (used elements) is decremented by 1
 * @return bool true if the veggie was destroyed, false if the storage is NULL or the index is out of bounds
 */
bool destroyVeggieInStorage(VEGGIE_STORAGE* storage, unsigned short index) {
    if (storage == NULL || index >= storage->used)
        return false;
    destroyVeggie(storage->data[index]);
    for (unsigned short i=index;i<storage->used-1;i++) {
        storage->data[i] = storage->data[i+1];
    }
    storage->used--;
    return true;
}
