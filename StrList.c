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
         Node* current = Strlist->head;// Start from the head of the list
        for (int i = 0; i < index && current; i++) {
        current = current->next;// Move to the next node
    }
        // If current is not NULL, print the data at the specified index
        if (current) {
        printf("%s\n", current->data);
    }
}

// Return the total number of characters in all the data elements of the StrList
int StrList_printLen(const StrList* Strlist){
     Node* current = Strlist->head;// Start from the head of the list
     int amountChars =0; // Initialize the total character count
     while (current)
     {
        amountChars+=strlen(current->data); // Add length of current data to total
        current=current->next;// Move to the next node
    
     }
     return amountChars;
}

// Count the occurrences of a specific data element in the StrList
int StrList_count(StrList* StrList, const char* data){
    // Start from the head of the list
     Node* current = StrList->head;
     int count=0; // Initialize the count of occurrences
     while (current)
     {
        // If current node's data the same  , increment count
        if(strcmp(current->data, data) == 0){
            count++;
        }
        current= current->next;
     }
     return count;
}

// Remove all occurrences of a specific data element from the StrList
void StrList_remove(StrList* StrList, const char* data) {
    Node* current = StrList->head; // Start from the head of the list
    Node* prev = NULL; // Initialize pointer to prev node
    Node* temp;  // Temporary node pointer for memory deallocation


    while (current != NULL) {
        
         // If current node's data the same  ,
        if (strcmp(current->data, data) == 0) {
            // If current node is the head
            if (current == StrList->head) {
                StrList->head = current->next;// Update head to next node
                StrList->size--; // Decrement the size of the list
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

// Remove the node at the specified index from the StrList
void StrList_removeAt(StrList* StrList, int index){
    Node* current =StrList->head;
    Node* prev=NULL;
    int count = 0;
        // Traverse the list until reaching the specified index or end of list
    while(current != NULL && count < index){
        prev=current; // Save current node as previous
        current=current->next; // Move to the next node
        count++; // Increment the count of nodes visited
    }
     // If current is NULL, index is out of range, so return
    if(current==NULL){
        return;
    }
    // If current node is the head
    if(current==StrList->head){
        StrList->head = current->next; // Update head to next node
        StrList->size--; // Decrement the size of the list
    }
    else{
    prev->next=current->next;
    StrList->size--;

    }
}

// Create a  copy of the StrList
StrList* StrList_clone(const StrList* StrList){
    nweStrList* ret = StrList_alloc(); // Allocate memory for new StrList
    Node* old = StrList->head;  // Start from the head of original list
    Node** copy = &(ret->head); // Pointer to pointer for updating copied list
    ret->size = StrList->size; // Set size of copy List

    while(old) {
        *copy = Node_alloc(old->data,NULL);  // Allocate memory for new node
        old = old->next; // Move to the next node in original list
        copy = &((*copy)->next); // Move to the next pointer in copied list
    }
    return ret;
}

// Reverse the order of nodes in the StrList
void StrList_reverse( StrList* StrList){
    Node* prev = NULL; // Initialize pointer 
    Node* current = StrList->head;// Start from the head of the list
    Node* next = NULL;  // Initialize pointer

    while (current)
    {
        next = current->next; // Save next node
        current->next = prev;  // Reverse the pointer
        prev = current;
        current = next;
    }
    
    StrList->head=prev;
    


}
 
// Sort the StrList in lexicographical order
void StrList_sort(StrList* StrList) {
    int swapped; // Flag to indicate whether swapping has occurred
    Node *ptr; // Pointer for current node
    Node *lptr = NULL; // Pointer for last checked node

    // Check if the list is empty
    if (StrList->head == NULL)
        return;
    //  bubble sort until no more swaps are needed
    do {
        swapped = 0; // Reset swapped flag
        ptr = StrList->head;  // Start from the head of the list

        while (ptr->next != lptr) {
            if (strcmp(ptr->data, ptr->next->data) > 0) {
                // Compare adjacent nodes and swap if necessary
                char* temp = ptr->data; // Swap data
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;// Set swapped flag
            }
            ptr = ptr->next; // Move to the next node
        }
        lptr = ptr;
    } while (swapped); // Repeat until no more swaps are needed
}
/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */

int StrList_isSorted(StrList* StrList){
    Node* current = StrList->head;// Start from the head of the list
    while (current&&current->next)
    {
        // If any adjacent nodes are out of order, return 0 (not sorted)
        if(strcmp(current->next->data,current->data)<0){
            return 0;
        }
        current=current->next;// Move to the next node
    }
    return 1;
}





