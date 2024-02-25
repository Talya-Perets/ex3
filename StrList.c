#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"


struct _StrList;
typedef struct _StrList StrList;
typedef struct Node Node;

struct _StrList {
    Node* head;
    size_t size;
};

typedef struct Node {
    char* data;
    Node* next;
} Node;

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
     if (list == NULL) {
            return NULL;
     }
    if (list != NULL) {
        list->head = NULL;
        list->size=0;
    }
    return list;
}

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


size_t StrList_size(const StrList* StrList){
   
    return StrList->size;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) {
        return;
    }
    
    char* newData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (newData == NULL) {
        return; 
    }   
    strcpy(newData,data);
    Node* newNode = Node_alloc(newData,NULL);

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


void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (StrList == NULL || data == NULL || index < 0) {
        return; 
    }

    char* newData = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (newData == NULL) {
        return; 
    } 

    strcpy(newData,data);
     Node* newNode=Node_alloc(newData,NULL);
    newNode->data =newData; 
   

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


char* StrList_firstData(const StrList* StrList){
    if (StrList->head) {
        return StrList->head->data;
    }
    return NULL;
}

void StrList_print(const StrList* StrList){
  if(StrList==NULL||StrList->head==NULL){
    printf("\n");
    return;
  }
    Node* current = StrList->head;
    if(current){
    printf("%s",current->data);
    current = current->next;
     }
    while (current)
    {
        printf(" %s",current->data);
        current = current->next;
        
    }   
     printf("\n");
}

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
