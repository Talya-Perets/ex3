#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"


struct _StrList;
typedef struct _StrList StrList;
typedef struct Node Node;

// Define the structure of the linked list

struct _StrList {
    Node* head; // Pointer to the first node in the list
    size_t size;  // Number of elements in the list
};

// Define the structure of a node in the linked list

typedef struct Node {
    char* data;  // Data stored in the node
    Node* next;  // Pointer to the next node
} Node;

// Function to allocate memory for a new empty StrList

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
     if (list == NULL) {
         // if allocation failed
            return NULL;
     }
        // Initialize the list

    if (list != NULL) {
        list->head = NULL;
        list->size=0;
    }
    return list;
}

// Function to allocate memory for a new node with given data and next pointer
Node* Node_alloc(char* data, Node* next){
     Node* newNode = (Node*)malloc(sizeof(Node));
         if (newNode == NULL) {
            return NULL;
        }
        newNode->data=data;
        newNode->next=next;
return newNode;
}

void StrList_free(StrList* StrList) {
    if (StrList) {
        Node* current = StrList->head;
        while (current) {
            Node* next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
        free(StrList);
    }
}

// Function to clean the StrList, freeing memory of all nodes but keeping the list structure

void StrList_clean(StrList* StrList) {
    if (StrList) {
        Node* current = StrList->head;
        while (current) {
            Node* next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
        StrList->head = NULL; 
    }
}

// Function to get the size of the StrList

size_t StrList_size(const StrList* StrList){
   
    return StrList->size;
}
// Function to insert a new node with data at the end of the StrList

void StrList_insertLast(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) {
        return;
    }
       // Allocate memory for the new data
 
    char* newData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (newData == NULL) {
        return; // if allocation failed
    }   
    strcpy(newData,data);
        // Create a new node
    Node* newNode = Node_alloc(newData,NULL);
    
    // Insert the new node at the end of the list
    if (StrList->head == NULL) {
        StrList->head = newNode;
        StrList->size++;
        return;
    }

    Node* current = StrList->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    StrList->size++;
}

// Function to insert a new node with data at a specific index in the StrList

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (StrList == NULL || data == NULL || index < 0) {
        return; 
    }
    // Allocate memory for the new data
    char* newData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (newData == NULL) {
        return; // if allocation failed
    } 

    strcpy(newData,data);
        // Create a new node

     Node* newNode=Node_alloc(newData,NULL);
    newNode->data =newData; 
   
    // Insert the new node at the specified index

    if (index == 0) {
        newNode->next = StrList->head;
        StrList->head = newNode;
        StrList->size++;
        return;
    }

    Node* current = StrList->head;
    for (int i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        free(newNode->data);
        free(newNode);
        return; 
    }
    newNode->next = current->next;
    current->next = newNode;
    StrList->size++;
}

// Function to get the data of the first node in the StrList

char* StrList_firstData(const StrList* StrList){
    if (StrList->head) {
        return StrList->head->data;
    }
    return NULL;
}

// Function to print the entire StrList

void StrList_print(const StrList* StrList){
  if(StrList==NULL||StrList->head==NULL){
    printf("\n");// If the list is empty or NULL, print a newline and return
    return;
  }
    Node* current = StrList->head;
    if(current){
        // Print the data of the first node without space
    printf("%s",current->data);
    current = current->next;// Move to the next node
     }
    while (current)
    {
        printf(" %s",current->data);// Print the data of the current node with a space separator
        current = current->next;// Move to the next node
        
    }   
     printf("\n");
}

// Function to print the data at a specific index in the StrList
void StrList_printAt(const StrList* Strlist,int index){
        Node* current = Strlist->head;
        for (int i = 0; i < index && current; i++) {
        current = current->next; // Move to the node at the specified index
    }
        if (current) {
        printf("%s\n", current->data);// If the node exists, print its data followed by a newline
    }
}

int StrList_printLen(const StrList* Strlist){
     Node* current = Strlist->head;
     int amountChars =0;
     while (current)
     {
        amountChars+=strlen(current->data);// Add the length of each node's data to the total
        current=current->next;// Move to the next node
    
     }
     return amountChars;
}

int StrList_count(StrList* StrList, const char* data){
     Node* current = StrList->head;
     int count=0;
     while (current)
     {
        if(strcmp(current->data, data) == 0){  // Compare the data of each node with the given data
            count++; // Increment count if a match is found
        }
        current= current->next;// Move to the next node
     }
     return count;
}

void StrList_remove(StrList* StrList, const char* data) {
    Node* current = StrList->head;
    Node* prev = NULL;
    Node* temp;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (current == StrList->head) { // If the node to remove is the head, update the head pointer
                StrList->head = current->next;
                StrList->size--;
            } else {
                prev->next = current->next;  // Otherwise, bypass the current node
                StrList->size--;
            }
            temp = current;
            current = current->next; // Move to the next node
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
    nweStrList* ret = StrList_alloc();/ Allocate memory for the new StrList
    const Node* old = StrList->head; 
    Node** copy = &(ret->head);
    ret->size = StrList->size;

    while(old) {
        *copy = Node_alloc(old->data,NULL);// Create a new node with the same data
        old = old->next;
        copy = &((*copy)->next);// Move to the next pointer in the copy list
    }
    return ret;
}


void StrList_reverse( StrList* StrList){
    Node* prev = NULL;
    Node* current = StrList->head;
    Node* next = NULL;

    while (current)
    {
        next = current->next;// Store the next node
        current->next = prev;// Reverse the link
        prev = current;
        current = next;
    }
    
    StrList->head=prev;// Update the head pointer to the last node (which is now the first)
    


}

void StrList_sort(StrList* StrList) {
    int swapped; //to indicate whether any swaps were made during a pass
    Node *ptr1; // Pointer for traversing the list
    Node *lptr = NULL; // Pointer to mark the last node that was swapped during a pass

    if (StrList->head == NULL)
        return;

    do {
        swapped = 0;// Reset the swapped flag for each pass
        ptr1 = StrList->head;// Start traversing from the head of the list

        while (ptr1->next != lptr) {
          // Traverse the list until the last swapped node (lptr)

            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                // Compare the data of the current node with the data of its next node
                // If the data of the current node is greater, swap their data
                char* temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1; // Set swapped flag to indicate a swap was made
            }
            ptr1 = ptr1->next;// Move to the next node
        }
        lptr = ptr1;// Update lptr to the last node visited during this pass
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





