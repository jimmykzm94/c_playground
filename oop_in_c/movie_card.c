#include <stdio.h>
#include <string.h>
#include "movie_card.h"

static ICard movieCard;
static char owner[50];
static float total = 0;
static int coupon = 0;

static void topUp(float amount){
    total += amount;
    coupon++;
}

static float getBalance(){
    return total;
}

static char* getName(){
    return owner;
}

static void printInfo(){
    printf("Name: %s Amount:%.2f Coupon count: %d\n", owner, total, coupon);
}

ICard* MovieCard(const char* name, float initAmount){
    total = initAmount;
    strcpy(owner, name);

    movieCard.topUp = topUp;
    movieCard.getBalance = getBalance;
    movieCard.whoIsOwner = getName;
    movieCard.printInfo = printInfo;

    return &movieCard;
}

// int main(){
//     ICard *card = MovieCard("Jimmy", 50.0);
//     card->printInfo();
//     return 0;
// }