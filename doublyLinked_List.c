#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for listnode
struct ListNode
{
    struct ListNode *prev;
    struct ListNode *next;
    char *data;
};

// Func for make a new node
struct ListNode *createNode(const char *data)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!newNode)
    {
        fprintf(stderr, "Error to allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for string and data
    newNode->data = (char *)malloc(strlen(data) + 1);
    if (!newNode->data)
    {
        fprintf(stderr, "Error to allocate memory for string\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->data, data);

    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Func for add a node at the end of the list
struct ListNode *listAppend(struct ListNode **head, struct ListNode *item)
{
    if (!*head)
    {
        *head = item;
    }
    else
    {
        struct ListNode *tail = *head;
        while (tail->next)
        {
            tail = tail->next;
        }
        tail->next = item;
        item->prev = tail;
    }

    return item;
}

// Func for remove a node from the list
void listRemove(struct ListNode **head, struct ListNode *item)
{
    if (!item)
    {
        return;
    }

    if (item->prev)
    {
        item->prev->next = item->next;
    }
    else
    {
        *head = item->next;
    }

    if (item->next)
    {
        item->next->prev = item->prev;
    }

    free(item->data);
    free(item);
}

// Func for add a node after another
struct ListNode *listInsertAfter(struct ListNode *prevNode, struct ListNode *newNode)
{
    if (!prevNode || !newNode)
    {
        return NULL;
    }

    newNode->prev = prevNode;
    newNode->next = prevNode->next;

    if (prevNode->next)
    {
        prevNode->next->prev = newNode;
    }

    prevNode->next = newNode;

    return newNode;
}

// Func for add a node before another 
struct ListNode *listInsertBefore(struct ListNode **head, struct ListNode *nextNode, struct ListNode *newNode)
{
    if (!nextNode || !newNode)
    {
        return NULL;
    }

    newNode->prev = nextNode->prev;
    newNode->next = nextNode;

    if (nextNode->prev)
    {
        nextNode->prev->next = newNode;
    }
    else
    {
        *head = newNode;
    }

    nextNode->prev = newNode;

    return newNode;
}

// Func for print the list
void printList(struct ListNode *head)
{
    struct ListNode *current = head;
    while (current != NULL)
    {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Func for free memory
void freeList(struct ListNode *head)
{
    while (head != NULL)
    {
        struct ListNode *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

// Func for shuffle list
void listShuffle(struct ListNode **head)
{
    int count = 0;
    struct ListNode *current = *head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    if (count < 2)
    {
        return; // nothing to shuffle if there are less than 2 elements
    }

    // Alghoritm for shuffle the list
    for (int i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        struct ListNode *node_i = *head;
        for (int k = 0; k < i; k++)
        {
            node_i = node_i->next;
        }

        struct ListNode *node_j = *head;
        for (int k = 0; k < j; k++)
        {
            node_j = node_j->next;
        }

        // Exchange value of nodes i and j
        char *temp = node_i->data;
        node_i->data = node_j->data;
        node_j->data = temp;
    }
}

int main()
{
    struct ListNode *myLinkedList = NULL;

    // Adds value to list
    listAppend(&myLinkedList, createNode("Item1"));
    listAppend(&myLinkedList, createNode("Item2"));
    listAppend(&myLinkedList, createNode("Item3"));

    // Print list
    printf("List: \n");
    printList(myLinkedList);

    // Remove a node from the list
    listRemove(&myLinkedList, myLinkedList->next);

    // print list after remove
    printf("List after remove: \n");
    printList(myLinkedList);

    // insert a node after another
    listInsertAfter(myLinkedList, createNode("New Item"));

    // print list after insert
    printf("List after the insert: \n");
    printList(myLinkedList);

    // insert a node before another 
    listInsertBefore(&myLinkedList, myLinkedList->next, createNode("New Item Before"));

    // print the list before another
    printf("List before another insert: \n");
    printList(myLinkedList);

    // Shuffle list
    listShuffle(&myLinkedList);

    // print shuffled list
    printf("Shuffled list: \n");
    printList(myLinkedList);

    // Free memory
    freeList(myLinkedList);

    return 0;
}

