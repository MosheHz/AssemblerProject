#include "directive.h"


Label* dire_andler(char *str, int line){
    Label *head = NULL, *curr;
    char type[LEN], *comma = ",\n";

    /*Copy the directive type to a separate buffer for processing.*/
    strcpy(type, str);

    while((str = strtok(NULL, comma)) != NULL){

        /*Check if the token is a legal label, if not, set the 'error_flag'.*/
        if(!is_legal_label(str, line)){
            error_flag = ON;
            continue;
        }

        /*Create a new Label object for the token. if the allocation of memory failed return NULL.*/
        if((curr = create_label(str)) == NULL)
            break;

        /*Set the label type based on the directive type.*/
        if(strcmp(type, EXTERN_ID) == 0)
            strcpy(curr->type, EX);
        else{
            strcpy(curr->type, EN);
            curr->location = line;
        }

        put_label_in_list(&head, curr); /*Add the label to the linked list.*/
    }
    /*If loop ended because memory allocation problem.*/
    if(str != NULL){
        free_label_list(head);
        return NULL;
    }
    /*If no labels were legal in the directive, create an empty label*/
    if(head == NULL){
        if((head = create_label(NULL)) == NULL)
            return NULL;
    }

    return head;
}
