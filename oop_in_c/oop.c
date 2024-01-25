#include <stdio.h>
#include <string.h>
#include "icard.h"
#include "shopping_card.h"
#include "movie_card.h"

int main(int arg, char *argv[]){
    ICard *card = NULL;

    if(arg < 3){
        printf("Arg: TYPE NAME\n");
        return 1;
    }

    if(strcmp(argv[1], "shopping") == 0){
        card = ShoppingCard(argv[2], 50.0);
    }
    else if(strcmp(argv[1], "movie") == 0){
        card = MovieCard(argv[2], 50.0);
    }

    if(card != NULL){
        card->printInfo();
        printf("Name: %s\n", card->whoIsOwner());
    }
    return 0;
}