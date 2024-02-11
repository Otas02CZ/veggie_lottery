//AUTHOR: Otakar Kočí
//DATE: 11/2/2024
//FILE: main.c
//DESCRIPTION: Main file for the project, creates storages, fills them and then
//randomly selects a veggie and a message to print, then deallocates the storages

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "veggie.h"
#include "message.h"

int main() {
    //create storages and check for correct creation
    VEGGIE_STORAGE* veggies = createVeggieStorage(10);
    if (veggies == NULL) {
        printf("Failed to create place for our veggies\n");
        return EXIT_FAILURE;
    }
    MESSAGE_STORAGE* messages = createMessageStorage(10);
    if (messages == NULL) {
        printf("Failed to create place for our messages\n");
        deleteVeggieStorage(veggies);
        return EXIT_FAILURE;
    }
    //randomize random by time
    srand(time(NULL));

    //fill veggies
    addVeggieToStorage(veggies, "carrot", "a", true);
    addVeggieToStorage(veggies, "potato", "a", true);
    addVeggieToStorage(veggies, "tomato", "a", true);
    addVeggieToStorage(veggies, "cucumber", "a", true);
    addVeggieToStorage(veggies, "onion", "an", false);
    addVeggieToStorage(veggies, "garlic", "a", false);
    addVeggieToStorage(veggies, "pumpkin", "a", true);
    addVeggieToStorage(veggies, "pepper", "a", true);
    addVeggieToStorage(veggies, "lettuce", "a", true);
    addVeggieToStorage(veggies, "cabbage", "a", true);
    addVeggieToStorage(veggies, "radish", "a", true);
    addVeggieToStorage(veggies, "beetroot", "a", false);
    addVeggieToStorage(veggies, "turnip", "a", false);
    addVeggieToStorage(veggies, "eggplant", "an", false);
    addVeggieToStorage(veggies, "zucchini", "a", false);
    addVeggieToStorage(veggies, "mushroom", "a", true);
    addVeggieToStorage(veggies, "broccoli", "a", true);
    addVeggieToStorage(veggies, "cauliflower", "a", true);
    addVeggieToStorage(veggies, "spinach", "a", false);
    addVeggieToStorage(veggies, "kale", "a", false);

    //fill messages
    addMessageToStorage(messages, "Today is your lucky day, cause you will eat %s %s all day!!\n", true);
    addMessageToStorage(messages, "Today is your unlucky day, cause you will eat %s %s all day!!\n", false);
    addMessageToStorage(messages, "A daily dish of %s %s will be yours now. Great isn't it!!\n", true);
    addMessageToStorage(messages, "A daily dish of %s %s will be yours now. Not so great is it!!\n", false);
    addMessageToStorage(messages, "Luckily you will eat %s %s for breakfast, for lunch and for dinner!!\n", true);
    addMessageToStorage(messages, "Unlucky you. You will eat %s %s for breakfast, for lunch and for dinner!!\n", false);
    addMessageToStorage(messages, "Oh yeah. You will eat %s %s for breakfast, for lunch and for dinner!!\n", true);
    addMessageToStorage(messages, "Oh no. You will eat %s %s for breakfast, for lunch and for dinner!!\n", false);

    // randomly select a starting index for veggies and messages and goodness of the pair good/bad|0/1
    __uint8_t veggieIndex = rand() % veggies->used;
    __uint8_t messageIndex = rand() % messages->used;
    __uint8_t goodness = rand() % 2;

    // use the starting index to find the first matching value in veggies
    while(veggies->veggies[veggieIndex]->isGood != goodness) {
        veggieIndex++;
        if (veggieIndex == veggies->used)
            veggieIndex = 0;
    }
    // use the starting index to find the first matching value in messages
    while(messages->messages[messageIndex]->isGood != goodness) {
        messageIndex++;
        if (messageIndex == messages->used)
            messageIndex = 0;
    }
    // print the selected message with the selected veggie
    printf(messages->messages[messageIndex]->text, veggies->veggies[veggieIndex]->article, veggies->veggies[veggieIndex]->name);
    // deallocate the storages
    deleteVeggieStorage(veggies);
    deleteMessageStorage(messages);
    return EXIT_SUCCESS;
}
