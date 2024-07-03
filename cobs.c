// reference: https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing

#include <stdio.h>
#include <string.h>

unsigned char encoded_buff[100];
void cobs_encode(const unsigned char *raw_buff, int size)
{
    // set array to 0
    memset(encoded_buff, 0, sizeof(encoded_buff));

    // method 1: index
    // int buff_index = 1; // because first index is always encoded
    // int encoded_index = 0; // because first index is always encoded
    // encoded_buff[encoded_index] = 1;

    // for(int i = 0; i < size; i++){
    //     if(raw_buff[i] == '\0'){
    //         encoded_index = buff_index;
    //         encoded_buff[encoded_index] = 1;
    //     }
    //     else{
    //         if(encoded_buff[encoded_index] == 0xFF){
    //             encoded_index = buff_index;
    //             encoded_buff[encoded_index] = 1;
    //             buff_index++;
    //         }
    //         encoded_buff[buff_index] = raw_buff[i];
    //         encoded_buff[encoded_index]++;
    //     }
    //     buff_index++;
    // }
    // encoded_buff[buff_index] = 0; // last index is null terminator

    // // print
    // for(int i = 0; i <= buff_index; i++){
    //     printf("%x ", encoded_buff[i]);
    // }
    // printf("\n");

    // method 2: pointer
    unsigned char *output_buff = (unsigned char *)encoded_buff;
    unsigned char *encoded = output_buff++;
    for (int i = 0; i < size; i++)
    {
        (*encoded)++;
        if (*raw_buff == '\0')
        {
            encoded = output_buff;
        }
        *(output_buff++) = *(raw_buff++);
    }
    (*encoded)++;

    // print
    unsigned char *display_buff = &encoded_buff[0];
    while (*display_buff != '\0')
    {
        printf("%x ", *(display_buff++));
    }
    printf("%x\n", *display_buff);
}

int main(void)
{
    unsigned char eg1[10] = {0};
    cobs_encode(eg1, 1);
    unsigned char eg2[10] = {0, 1, 0};
    cobs_encode(eg2, 3);
    return 0;
}