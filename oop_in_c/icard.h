#pragma once

// interface
typedef struct{
    void (*topUp)(float);
    float (*getBalance)();
    char *(*whoIsOwner)();
    void (*printInfo)();
} ICard;
