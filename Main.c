
 
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include "StrList.h"

int main() {
    StrList* strList = StrList_alloc();
    int choice;
    char* line = NULL;
    size_t bufsize = 0;
    char* word;
    int index;
    
    

    do{
    scanf("%d",&choice);

     switch (choice) {
         case 1: 
                scanf("%d",&index);
                getchar();
                getline(&line, &bufsize, stdin);
                word = strtok(line, " \n");
                while (word != NULL) {
                    StrList_insertLast(strList, word);
                    word = strtok(NULL, " \n");
                }                
                break;
        case 2:
            scanf("%d",&index);
            getline(&line, &bufsize, stdin);
            word = strtok(line, " \n");
            StrList_insertAt(strList,word,index);
           
            break;
        case 3:
            StrList_print(strList);
            printf("\n");
            break;
        
        case 4:
            printf("%ld\n",StrList_size(strList));
            break;
        
        case 5:
            scanf("%d",&index);
            StrList_printAt(strList,index);
            break;
        
        case 6:
           printf("%d\n",StrList_printLen(strList)) ;
           break;
        
        case 7:
           getchar(); 
           getline(&line, &bufsize, stdin);
           word = strtok(line, " \n");
           printf("%d\n",StrList_count(strList,word)); 
           break;
        case 8:
           getchar(); 
           getline(&line, &bufsize, stdin);
           word = strtok(line, " \n");
           StrList_remove(strList,word);

            break;
        case 9:
            scanf("%d",&index);
            StrList_removeAt(strList,index);
            break;
        case 10:
            StrList_reverse(strList);
            break;
        case 11:
            StrList_clean(strList);

           
            break;
        case 12:
            StrList_sort(strList);
            break;
        case 13:
            int isSort;
            isSort=StrList_isSorted(strList);
            
            if(isSort){
                printf("true \n");
            }
            else{
                printf("false \n");
            }
        
        
        default :
            break;

     }}

  
    while (choice != 0);
       
    free(line); 
    StrList_free(strList);
    return 0;
}
