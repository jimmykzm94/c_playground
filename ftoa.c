/* Float to ASCII */
#include <stdio.h>

// String buffer
char buff[60];
char *ftoa(float value, int dp)
{
    int index = 59;
    char negative = 0;

    if(value < 0)
    {
        value *= -1;
        negative = 1;
    }

    // Get dp
    int temp;
    int multi_10 = 1;
    for(int i = 0; i < dp; i++)
    {
        multi_10 *= 10;
    }
    temp = value * multi_10;
    for(int i = 0; i < dp; i++)
    {
        buff[index--] = 0x30 + temp % 10;
        temp /= 10;
    }

    // Dot
    buff[index--] = '.';

    // Get decimal
    if(temp == 0)
    {
        buff[index--] = '0';
    }
    while(temp != 0)
    {
        buff[index--] = 0x30 + temp % 10;
        temp /= 10;
    }

    // Negative
    if(negative)
    {
        buff[index--] = '-';
    }

    return &buff[++index];
}

int main(void)
{
    char *str = ftoa(123.1422, 3);
    printf("%s\n", str);

    str = ftoa(0.1422, 3);
    printf("%s\n", str);

    str = ftoa(-123.1422, 3);
    printf("%s\n", str);
}
