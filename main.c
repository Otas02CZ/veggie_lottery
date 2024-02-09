#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define ARTICLE_MAX_LEN 4   //3+1
#define VEGGIE_NAME_LEN 21  //20+1
#define MAX_SHORT 65535
#define INCREMENT 10

typedef struct VEGGIE {
    char* name;
    char* article;
} VEGGIE;

typedef struct VEGGIE_STORAGE {
    VEGGIE* veggies;
    unsigned short used;
    unsigned short max;
} VEGGIE_STORAGE;

VEGGIE* createVeggie(char* veggieName, char* article) {
    if ((strlen(veggieName) >= VEGGIE_NAME_LEN) || (strlen(article) >= ARTICLE_MAX_LEN))
        return NULL;
    VEGGIE* veggie = malloc(sizeof(VEGGIE));
    if (veggie == NULL)
        return NULL;
    if ((veggie->article = malloc(ARTICLE_MAX_LEN * sizeof(char))) == NULL)
        return NULL;
    if ((veggie->name = malloc(VEGGIE_NAME_LEN * sizeof(char))) == NULL) {
        free(veggie->article);
        return NULL;
    }
    strcpy(veggie->article, article);
    strcpy(veggie->name, veggieName);
    return veggie;
}

void deleteVeggie(VEGGIE* veggie) {
    if (veggie == NULL)
        return;
    if (veggie->article != NULL)
        free(veggie->article);
    if (veggie->name != NULL)
        free(veggie->name);
}

int main() {
    const int veggiesCount = 15;
    const int veggieNameLen = 41;
    char** veggies;
    if ((veggies = malloc(veggiesCount * sizeof(char*))) == NULL)
        return EXIT_FAILURE;
    for (int i=0;i<veggiesCount;i++) {
        if ((veggies[i] = malloc(veggieNameLen * sizeof(char))) == NULL) {
            int j = 0;
            while (veggies[j] != NULL || j < veggiesCount) {
                free(veggies[j]);
                j++;
            }
            free(veggies);
            return EXIT_FAILURE;
        }
    }
    strcpy(veggies[0], "potato");
    printf("Today is your lucky day, cause you will eat %s!!\n", veggies[0]);
    for (int i=0;i<veggiesCount;i++) {
        free(veggies[i]);
    }
    free(veggies);
    return EXIT_SUCCESS;
}
