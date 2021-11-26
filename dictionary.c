#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct dict
{
    uint8_t key;
    uint8_t value;
    struct dict *next;
};

void PrintData(struct dict *data);
void Append(uint8_t key, uint8_t value);
void Add(uint8_t index, uint8_t key, uint8_t value);
void Delete(uint8_t index);
uint8_t GetCount();
void PrintCount();

struct dict *data = NULL;

int main(void)
{
    // Testing
    printf("Testing\n");
    struct dict *test = NULL;
    struct dict *one = malloc(sizeof(struct dict));
    struct dict *two = malloc(sizeof(struct dict));
    struct dict *three = malloc(sizeof(struct dict));

    one->key = 1;
    one->value = 23;

    two->key = 2;
    two->value = 24;

    three->key = 3;
    three->value = 25;

    one->next = two;
    two->next = three;
    three->next = NULL;
    test = one;

    PrintData(test);

    struct dict *four = malloc(sizeof(struct dict));
    four->key = 4;
    four->value = 45;
    two->next = four;
    four->next = three;

    PrintData(test);

    // Using helper function
    printf("Helper functions\n");
    Append(1, 53);
    Append(2, 54);
    Append(3, 55);
    Append(4, 55);
    Append(5, 55);
    Add(1, 33, 33);
    PrintCount();
    PrintData(data);

    Delete(4);
    PrintCount();
    PrintData(data);

    free(test);
    free(data);
    return 0;
}

void PrintData(struct dict *data)
{
    struct dict *temp = data;
    while(temp != NULL)
    {
        printf("Key: %d Value: %d\n", temp->key, temp->value);
        temp = temp->next;
    }
}

void Append(uint8_t key, uint8_t value)
{
    struct dict *newData = malloc(sizeof(struct dict));
    newData->key = key;
    newData->value = value;

    if(data == NULL)
    {
        data = newData;
        return;
    }

    struct dict *temp = data;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newData;
}

void Add(uint8_t index, uint8_t key, uint8_t value)
{
    if(GetCount() <= index)
    {
        printf("Error to set!\n");
        return;
    }

    struct dict *newData = malloc(sizeof(struct dict));
    newData->key = key;
    newData->value = value;

    int count = 0;
    struct dict *prev = NULL;
    struct dict *next = data;
    while(next != NULL)
    {
        if(index == 0)
        {
            newData->next = next;
            data = newData;

            return;
        }
        else if(count == index)
        {
            prev->next = newData;
            newData->next = next;

            return;
        }
        else
        {
            prev = next;
            next = next->next;
        }
        count++;
    }
}

void Delete(uint8_t index)
{
    if(GetCount() <= index)
    {
        printf("Delete error!\n");
        return;
    }

    uint8_t count = 0;
    struct dict *prev = NULL;
    struct dict *next = data;
    while(next != NULL)
    {
        if(index == 0)
        {
            data = next->next;
            free(next);

            return;
        }
        else if(count == index)
        {
            prev->next = next->next;
            free(next);

            return;
        }
        else
        {
            prev = next;
            next = next->next;
        }
        count++;
    }
}

uint8_t GetCount()
{
    uint8_t count = 0;

    struct dict *temp = data;
    while(temp != NULL)
    {
        temp = temp->next;
        count++;
    }

    return count;
}

void PrintCount()
{
    printf("Count: %d\n", GetCount());
}