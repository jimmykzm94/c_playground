#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

void appendNode(struct Node **list, int data)
{
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
    current->data = data;
    current->next = NULL;

    if(*list == NULL)
    {
        *list = current;
        return;
    }

    struct Node* last = *list;
    while(last->next != NULL)
    {
        last = last->next;
    }
    last->next = current;
}

void deleteNode(struct Node** list, int data)
{
    struct Node *current;
    struct Node *head = *list;
    // First node
    if(head != NULL && (head->data == data))
    {
        current = head;
        *list = head->next;
        free(current);
        return;
    }

    // Second node and above
    struct Node *prev = head;
    head = head->next;
    while(head != NULL)
    {
        if(head->data == data)
        {
            current = head;
            prev->next = head->next;
            free(current);
            return;
        }
        prev = head;
        head = head->next;
    }
}

void printData(struct Node* list)
{
    while(list != NULL)
    {
        printf("The data is %d\n", list->data);
        list = list->next;
    }
}

void freeList(struct Node** list)
{
    struct Node* next;
    struct Node* current = *list;
    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *list = NULL;
}

int main(void)
{
    struct Node* head = NULL;

    printf("Appending data\n");
    appendNode(&head, 11);
    appendNode(&head, 22);
    appendNode(&head, 33);
    appendNode(&head, 44);
    appendNode(&head, 55);
    printData(head);

    printf("Deleting second node\n");
    deleteNode(&head, 22);
    printData(head);

    printf("Deleting first node\n");
    deleteNode(&head, 11);
    printData(head);

    freeList(&head);

    return 0;
}