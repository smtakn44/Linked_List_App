/*
    SINGLE LINK LIST IMPLEMENTATION BY SAMET AKIN
    12.04.2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[20]; // city name
    struct node *next;
};

// prototypes
struct node *initializeList(struct node *head);
void displayList(struct node *head);

struct node *insertNodeAtTheBegining(struct node *head);
void insertNodeAtTheEnd(struct node *head);
void insertNodeAfterNode(struct node *head, char *city);  // find this node and insert after this
void insertNodeBeforeNode(struct node *head, char *city); // find this node and insert before this

struct node *deleteNodeAtTheBegining(struct node *head);
void deleteNodeAtTheEnd(struct node *head);
void deleteNodeAfterNode(struct node *head, char *city);  // find this node and delete after this
void deleteNodeBeforeNode(struct node *head, char *city); // find this node and delete before this

struct node *deleteAll(struct node *head);
void findNodeOrder(struct node *head, char *city);

int main()
{
    struct node *head = NULL;
    int option = 1;

    while (option != -1)
    {
        printf("0-Initialize the List\n1-Display the List\n2-Insert Node at the Begining\
        \n3-Insert Node at the End\n4-Insert a Node Before a Node\n5-Insert a Node After a Node\
        \n6-Delete Node at the Begining\n7-Delete Node at the End\n8-Delete a Node Before a Node\
        \n9-Delete a Node After a Node\n10-Delete All List\n11-Find Node Order\nPlease choose or press -1 to quit:");
        scanf("%d", &option);

        switch (option)
        {
        case -1:
            break;
        case 0:
            head = initializeList(head);
            break;
        case 1:
            displayList(head);
            break;
        case 2:
            head = insertNodeAtTheBegining(head);
            break;
        case 3:
            insertNodeAtTheEnd(head);
            break;
        case 4:
        {
            char city[20];
            printf("Please enter the city that you want to insert a node before this city:\n");
            scanf("%s", city);
            insertNodeBeforeNode(head, city);
        }
        break;
        case 5:
        {
            char city[20];
            printf("Please enter the city that you want to insert a node after this city:\n");
            scanf("%s", city);
            insertNodeAfterNode(head, city);
        }
        break;
        case 6:
            head = deleteNodeAtTheBegining(head);
            break;
        case 7:
            deleteNodeAtTheEnd(head);
            break;
        case 8:
        {
            char city[20];
            printf("Please enter the city that you want to delete a node before this city:\n");
            scanf("%s", city);
            deleteNodeBeforeNode(head, city);
        }
        break;
        case 9:
        {
            char city[20];
            printf("Please enter the city that you want to delete a node after this city:\n");
            scanf("%s", city);
            deleteNodeAfterNode(head, city);
        }
        break;
        case 10:
            head = deleteAll(head);
            break;
        case 11:
        {
            char city[20];
            printf("Please enter the city that you want to find the order\n");
            scanf("%s", city);
            findNodeOrder(head, city);
        }
        break;
        default:
            puts("Invalid Input");
            break;
        }
    }
    return 0;
}

struct node *initializeList(struct node *head)
{
    if (head != NULL)
    {
        puts("The list should be empty to initialize.");
        return head;
    }

    int length = 0;
    printf("Please enter the list length:\n");
    scanf("%d", &length);
    head = insertNodeAtTheBegining(head);
    for (int i = 0; i < length - 1; i++)
    {
        insertNodeAtTheEnd(head);
    }
    return head;
}

void displayList(struct node *head)
{
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("\ncity: %s\n", temp->name);
        temp = temp->next;
    }
    return;
}

struct node *insertNodeAtTheBegining(struct node *head)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    printf("Please enter the city name:\n");
    scanf("%s", new_node->name);
    new_node->next = head;
    head = new_node;
    return head;
}

void insertNodeAtTheEnd(struct node *head)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    printf("Please enter the city name:\n");
    scanf("%s", new_node->name);
    new_node->next = NULL;

    struct node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    return;
}

void insertNodeAfterNode(struct node *head, char *city)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    printf("Please enter the city name:\n");
    scanf("%s", new_node->name);

    struct node *temp = head;
    while (temp != NULL && strcmp(temp->name, city) != 0)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("The city is not found.\n");
        free(new_node);
        return;
    }
    struct node *post_temp = temp->next;
    temp->next = new_node;

    new_node->next = post_temp;
    return;
}

void insertNodeBeforeNode(struct node *head, char *city)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    printf("Please enter the city name:\n");
    scanf("%s", new_node->name);

    struct node *temp = head;
    struct node *pre_temp;
    while (temp != NULL && strcmp(temp->name, city) != 0)
    {
        pre_temp = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("The city is not found.\n");
        free(new_node);
        return;
    }
    pre_temp->next = new_node;
    new_node->next = temp;
    return;
}

struct node *deleteNodeAtTheBegining(struct node *head)
{
    struct node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

void deleteNodeAtTheEnd(struct node *head)
{
    struct node *temp = head;
    struct node *pre_temp = temp;
    while (temp->next != NULL)
    {
        pre_temp = temp;
        temp = temp->next;
    }
    pre_temp->next = NULL;
    free(temp);
    return;
}

void deleteNodeAfterNode(struct node *head, char *city)
{
    struct node *temp = head;
    while (temp != NULL && strcmp(temp->name, city) != 0)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("The city is not found.\n");
        return;
    }
    struct node *post_temp = temp->next;
    temp->next = post_temp->next;
    free(post_temp);
    return;
}

void deleteNodeBeforeNode(struct node *head, char *city)
{
    // here temp->next->next is the city we search
    struct node *temp = head;
    while (temp->next->next != NULL && strcmp(temp->next->next->name, city) != 0)
    {
        temp = temp->next;
    }
    if (temp->next->next == NULL)
    {
        printf("The city is not found.\n");
        return;
    }
    struct node *dummy = temp->next; // the node before the node we search
    temp->next = temp->next->next;
    free(dummy);
    return;
}

struct node *deleteAll(struct node *head)
{
    while (head != NULL)
    {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }
    return head; // it returns NULL since we delete all node
}

void findNodeOrder(struct node *head, char *city)
{
    int order = 1;
    struct node *temp = head; //  not to change the head pointer, define a temp pointer
    while (temp != NULL && strcmp(temp->name, city) != 0)
    {
        temp = temp->next;
        order++;
    }

    if (temp == NULL)
    {
        puts("The city is not found");
        return;
    }

    printf("Node order is %d\n", order);
    return;
}