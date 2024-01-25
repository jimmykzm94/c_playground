#include <stdio.h>

/// @brief Check value is power of 2
/// @param value Value to check
/// @return 0=False, 1=True
int check_power_two(int value){
    // Return 0 if less than 2
    if(value < 2){
        return 0;
    }

    // Start from 2
    int temp = 2;
    do{
        if(temp == value){
            return 1;
        }
        temp *= 2;
    } while(temp <= value);

    return 0;
}

int main(void){
    unsigned char tests[] = {0, 1, 8, 16, 10, 25, 100, 128};
    for(int i = 0; i < sizeof(tests); i++){
        if(check_power_two(tests[i])){
            printf("%d is power of 2\n", tests[i]);
        }else{
            printf("%d is not power of 2\n", tests[i]);
        }
    }
}