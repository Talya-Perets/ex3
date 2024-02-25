#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"


struct _StrList;
typedef struct _StrList StrList; 
typedef struct Node Node;

// Define a struct for the string linked list
struct _StrList {
    Node* head; // Pointer to the first node in the list
    size_t size; // Size of the list
};

 // Define a struct for a node in the linked list
typedef struct Node {
    char* data; // Pointer to hold string data
    Node* next; // Pointer to the next node in the list
} Node;

// Function to allocate memory for a new empty string list
StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList)); // Allocate memory for the list
     if (list == NULL) {
            return NULL; // Return NULL if memory allocation fails
     }
    if (list != NULL) {
        list->head = NULL; // Initialize head pointer to NULL
        list->size=0; // Initialize size to 0
    }
    return list;
}

// Function to allocate memory for a new node with given data and next pointer
Node* Node_alloc(char* data, Node* next){
     Node* newNode = (Node*)malloc(sizeof(Node));// Allocate memory for the new node
         if (newNode == NULL) {
            return NULL;/// Return NULL if memory allocation fails
        }
        newNode->data=data; // Set the data of the new node
        newNode->next=next; // Set the next pointer of the new node
return newNode;
}

// Function to free memory allocated for the string list
void StrList_free(StrList* StrList) {
    if (StrList) { // Check if the list pointer is not NULL
        Node* current = StrList->head; // Start from the head of the list
        while (current) { // Loop through all nodes in the list
            Node* next = current->next;
        
            // Free the data of the current node and the cuttent
            free(current->data);
            free(current);
            current = next; // Move to the next node
        }
        free(StrList);
    }
}

// Function to clean the string list without freeing the list itself
void StrList_clean(StrList* StrList) {
    if (StrList) {  // Check if the list pointer is not NULL
        Node* current = StrList->head; // Start from the head of the list
        while (current) { // Loop through all nodes in the list
            Node* next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
        StrList->head = NULL; 
    }
}

// Return the size of the StrList
size_t StrList_size(const StrList* StrList){
   
    return StrList->size;
}

// Insert a new node with data at the end of the StrList
void StrList_insertLast(StrList* StrList, const char* data) {
        // Check for NULL input
    if (StrList == NULL || data == NULL) {
        return;
    }
     // Allocate memory for the new data and copy the provided data
    char* newData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (newData == NULL) {
        return; 
    } 
    // Create a new node with the copied data  
    strcpy(newData,data);
    Node* newNode = Node_alloc(newData,NULL);

    // If the list is empty, set the new node as the head
    if (StrList->head == NULL) {
        StrList->head = newNode;
        StrList->size++;
        return;
    }

    // Find the last node and append the new node
    Node* current = StrList->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    StrList->size++;
}

// Insert a new node with data at the specified index in the StrList
void StrList_insertAt(StrList* StrList, const char* data, int index) {
        // Check for NULL input or negative index
    if (StrList == NULL || data == NULL || index < 0) {
        return; 
    }

    // Allocate memory for the new data and copy the provided data
    char* newData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (newData == NULL) {
        return; 
    } 
    // Create a new node with the copied data
    strcpy(newData,data);
     Node* newNode=Node_alloc(newData,NULL);
    newNode->data =newData; 
   
    // If index is 0, insert at the beginning
    if (index == 0) {
        newNode->next = StrList->head;
        StrList->head = newNode;
        StrList->size++;
        return;
    }

    // Find the node at (index - 1)
    Node* current = StrList->head;
    for (int i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        free(newNode->data);
        free(newNode);
        return; 
    }
    // Insert the new node between current and current->next
    newNode->next = current->next;
    current->next = newNode;
    StrList->size++;
}

// Return the data of the first node in the StrList
char* StrList_firstData(const StrList* StrList){
    if (StrList->head) {
        return StrList->head->data;
    }
    return NULL;
}

// Print all the data elements in the StrList
void StrList_print(const StrList* StrList){
  // Check if the StrList is empty or NULL
  if(StrList==NULL||StrList->head==NULL){
    printf("\n");
    return;
  }
    Node* current = StrList->head; // Start from the head of the list
    if(current){
    printf("%s",current->data); // Print the data of the head
    current = current->next;
     }
    while (current)
    {
        printf(" %s",current->data); // Print the data of the node
        current = current->next;
        
    }   
     printf("\n");
}
// Print the data at the specified index in the StrList
void StrList_printAt(const StrList* Strlist,int index){
        Node* current = Strlist->head;
        for (int i = 0; i < index && current; i++) {
        current = current->next;
    }
        if (current) {
        printf("%s\n", current->data);
    }
}

int StrList_printLen(const StrList* Strlist){
     Node* current = Strlist->head;
     int amountChars =0;
     while (current)
     {
        amountChars+=strlen(current->data);
        current=current->next;
    
     }
     return amountChars;
}

int StrList_count(StrList* StrList, const char* data){
     Node* current = StrList->head;
     int count=0;
     while (current)
     {
        if(strcmp(current->data, data) == 0){
            count++;
        }
        current= current->next;
     }
     return count;
}

void StrList_remove(StrList* StrList, const char* data) {
    Node* current = StrList->head;
    Node* prev = NULL;
    Node* temp;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (current == StrList->head) {
                StrList->head = current->next;
                StrList->size--;
            } else {
                prev->next = current->next;
                StrList->size--;
            }
            temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}


void StrList_removeAt(StrList* StrList, int index){
    Node* current =StrList->head;
    Node* prev=NULL;
    int count = 0;
    while(current != NULL && count < index){
        prev=current;
        current=current->next;
        count++;
    }
    if(current==NULL){
        return;
    }
    if(current==StrList->head){
        StrList->head = current->next;
        StrList->size--;
    }
    else{
    prev->next=current->next;
    StrList->size--;

    }
}
StrList* StrList_clone(const StrList* StrList){
    nweStrList* ret = StrList_alloc();
    const Node* old = StrList->head;
    Node** copy = &(ret->head);
    ret->size = StrList->size;

    while(old) {
        *copy = Node_alloc(old->data,NULL);
        old = old->next;
        copy = &((*copy)->next);
    }
    return ret;
}


void StrList_reverse( StrList* StrList){
    Node* prev = NULL;
    Node* current = StrList->head;
    Node* next = NULL;

    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    StrList->head=prev;
    


}

void StrList_sort(StrList* StrList) {
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    if (StrList->head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = StrList->head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                char* temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */

int StrList_isSorted(StrList* StrList){
    Node* current = StrList->head;
    while (current&&current->next)
    {
        if(strcmp(current->next->data,current->data)<0){
            return 0;
        }
        current=current->next;
    }
    return 1;
}





