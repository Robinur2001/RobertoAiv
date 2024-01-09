#include <stddef.h> 
#include <stdio.h>
#include <stdlib.h>

#define NODE(type, ptr) ((type)(ptr))

// struct for define node
typedef struct list_node 
{
    struct list_node *next;
} list_node;



// Func for create a new node
list_node *createNode() {
    list_node *newNode = NODE(list_node *, malloc(sizeof(list_node)));
    if (!newNode) 
    {
        fprintf(stderr, "Error to allocate node\n");
        exit(EXIT_FAILURE);
    }
    newNode->next = NULL;
    return newNode;
}

// Func for get the tail from the list
list_node *list_get_tail(list_node **head) 
{
    list_node *current_node = *head;
    list_node *last_node = NULL;
    while (current_node) 
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

// Func for add a node at the end of the list
list_node *list_append(list_node **head, list_node *item) 
{
    list_node *tail = list_get_tail(head);
    if (!tail) 
    {
        *head = item;
    } else 
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}

// Func for remove a node from the list
list_node *list_pop(list_node **head) 
{
    list_node *current_head = *head;
    if (!current_head) 
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

// Func for reverse the list 
list_node *list_reverse(list_node **head) 
{
    list_node *prev = NULL;
    list_node *current = *head;
    list_node *next = NULL;

    while (current != NULL) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev; //New point of start its the last node
    return prev;
}

// Struct for items in the list
struct string_item 
{
    list_node node;
    const char *string;
};

// Func for create a new item
struct string_item *string_item_new(const char *string) 
{
    struct string_item *item = NODE(struct string_item *, malloc(sizeof(struct string_item)));
    if (!item) 
    {
        fprintf(stderr, "Error to allocate string_item\n");
        exit(EXIT_FAILURE);
    }
    item->string = string;
    return item;
}

// Func for free the memory in the list
void free_list(list_node *head) 
{
    while (head != NULL) 
    {
        list_node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() 
{
    struct string_item *my_linked_list = NULL;

    // add items to list
    list_append((list_node **)&my_linked_list, (list_node *)string_item_new("Hello World"));
    list_append((list_node **)&my_linked_list, (list_node *)string_item_new("Test001"));
    list_append((list_node **)&my_linked_list, (list_node *)string_item_new("Test002"));
    list_append((list_node **)&my_linked_list, (list_node *)string_item_new("Last Item of the Linked List"));

    // print the list before remove
    printf("list before the remove: \n");
    struct string_item *string_item = my_linked_list;
    while (string_item) 
    {
        printf("%s\n", string_item->string);
        string_item = NODE(struct string_item *, string_item->node.next);
    }

    // remove and item from the list 
    struct string_item *removed_item = NODE(struct string_item *, list_pop((list_node **)&my_linked_list));
    if (removed_item) 
    {
        printf("Item removed: %s\n", removed_item->string);
        free(removed_item);
    } 
    else 
    {
        printf("list is empty, nothing to remove\n");
    }

    // print the list after the remove 
    printf("List after the remove: \n");
    string_item = my_linked_list;
    while (string_item) 
    {
        printf("%s\n", string_item->string);
        string_item = NODE(struct string_item *, string_item->node.next);
    }

    // Reverse list 
    list_reverse((list_node **)&my_linked_list);

    //  Print the reversed list
    printf("List reversed: \n");
    string_item = my_linked_list;
    while (string_item) 
    {
        printf("%s\n", string_item->string);
        string_item = NODE(struct string_item *, string_item->node.next);
    }

    // Free memory 
    free_list((list_node *)my_linked_list);

    return 0;
}
