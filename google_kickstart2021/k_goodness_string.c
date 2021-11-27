#include <stdio.h>
#include <strings.h>
#include <math.h>

int k_goodness_string(char *str, int length, int k)
{
    // get score
    int score = 0;
    for(int i = 1; i < (length / 2); i++)
    {
        if(str[i] != str[length-i+1])
            score++;
    }

    // number of operation
    if(score >= k)
    {
        return score - k;
    }
    return k - score;
}

int atoi(char *str, int size)
{
    int v = 0;
    for(int i = 0; i < size; i++)
    {
        v += (str[i] - 48) * (int)pow(10, size - i - 1);
    }
    return v;
}

void GetLenAndK(char *str, int *length, int *k)
{
    int count = 0;
    int index = 0;
    // get length
    char slen[10];
    while(str[index] != ' ')
    {
        slen[count++] = str[index++];
    }
    *length = atoi(slen, count);

    // get k
    count = 0;
    index++;
    char sk[10];
    while(str[index] != '\n')
    {
        sk[count++] = str[index++];
    }
    *k = atoi(sk, count);
}

// int main()
// {
//     // first line = number of case
//     // first case line = length of string, number of K
//     // second case line = string

//     int line = 1;
//     int case_num, case_index = 0;
//     int length, k;

//     FILE *file;
//     file = fopen("sample.txt", "r");
//     char str[60];
//     while(fgets(str, 60, file) != NULL)
//     {
//         // printf("%d ", strlen(str));
//         if(line == 1)
//         {
//             case_num = atoi(str, strlen(str) - 1);
//         } 
//         else if(line % 2 == 0)
//         {
//             GetLenAndK(str, strlen(str), &length, &k);
//             // printf("%d %d\n", length, k);
//         }
//         else
//         {
//             // printf("%d %d", length, k);
//             int a = k_goodness_string(str, length, k);
//             printf("Case #%d: %d\n", ++case_index, a);
//             if(case_index >= case_num)
//                 break;
//         }
//         line++;
//     }
//     fclose(file);

//     return 0;
// }

int main()
{
    int case_num, case_index = 0;
    int length, k;

    char str[20];
    // get case
    fgets(str, sizeof(str), stdin);
    case_num = atoi(str, strlen(str) - 1);

    while(case_index < case_num)
    {
        fgets(str, sizeof(str), stdin);
        GetLenAndK(str, &length, &k);

        fgets(str, sizeof(str), stdin);
        int a = k_goodness_string(str, length, k);
        printf("Case #%d: %d\n", ++case_index, a);
    }
}