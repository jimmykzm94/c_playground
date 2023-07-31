#include <stdio.h>
#include <stdint.h>

void bubble_sort(uint8_t* array, int size)
{
    for(int i = 0; i < size-1; i++)
    {
        for(int j = i + 1; j < size ; j++)
        {
            if (array[j-1] > array[j])
            {
                uint8_t temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
        }
    }
}


int main(void)
{
    uint8_t a[] = {2,9,3,5,4};
    bubble_sort(a, sizeof(a));
    for(int i = 0; i < sizeof(a); i++)
    {
        printf("%d\n",a[i]);
    }
	return 0;
}
