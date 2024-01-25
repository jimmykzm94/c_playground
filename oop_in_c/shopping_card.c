#include <stdio.h>
#include <string.h>
#include "shopping_card.h"

static ICard shoppingCard;
static char owner[50];
static float total = 0;

static void topUp(float amount){
    total += amount * 1.5;
}

static float getBalance(){
    return total;
}

static char* getName(){
    return owner;
}

static void printInfo(){
    printf("Name: %s Amount:%f with 1.5%% times bonus everytime top up\n", owner, total);
}

ICard* ShoppingCard(const char* name, float initAmount){
    total = initAmount;
    strcpy(owner, name);

    shoppingCard.topUp = topUp;
    shoppingCard.getBalance = getBalance;
    shoppingCard.whoIsOwner = getName;
    shoppingCard.printInfo = printInfo;

    return &shoppingCard;
}