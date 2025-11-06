#include <stdio.h>
#include <stdlib.h>

// Node structure definition
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to insert a node at the end of the list
void insertNode(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    Node* temp = *head;
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode; // If list is empty, new node becomes the head
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode; // Add new node at the end
    }
}

// Function to print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to delete a node by value
void deleteNode(Node** head, int data) {
    Node *temp = *head, *prev = NULL;

    // If the node to be deleted is the head
    if (temp != NULL && temp->data == data) {
        *head = temp->next; // Move head to the next node
        free(temp);
        return;
    }

    // Search for the node to be deleted
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    // If the node was not found
    if (temp == NULL) {
        printf("Node with data %d not found.\n", data);
        return;
    }

    // Unlink the node from the list
    prev->next = temp->next;
    free(temp);
}

int main() {
    Node* head = NULL; // Initialize an empty list

    insertNode(&head, 10); // Insert nodes
    insertNode(&head, 20);
    insertNode(&head, 30);

    printf("Linked List: ");
    printList(head); // Print list
    
    deleteNode(&head, 20); // Delete a node
    printf("Linked List after deletion: ");
    printList(head); // Print list after deletion

    return 0;
}
