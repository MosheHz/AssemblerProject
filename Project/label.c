#include "label.h"


Label* create_label(char *name){
    Label *temp;
    char *empty = NO_LABEL;

    /*If the name is NULL, assign an empty label name.*/
    if(name == NULL)
        name = empty;

    /*Allocate memory for the Label node.*/
    if((temp = (Label *)calloc(1, sizeof(Label))) == NULL){
        PRINT(ERR_ALLOC_MEM);
        return NULL;
    }

    /*Copy the label name to the node and set the next pointer to NULL.*/
    strcpy(temp->name, name);
    temp->next = NULL;
    return temp;
}


int put_label_in_list(Label **head, Label *new){
    Label *temp = *head;

    /*If the label list is empty, add the new label as the head.*/
    if(temp == NULL){
        temp = new;
        *head = temp;
    }

    else{
        /*Check for duplicate labels and handle conflicts between external and non-external labels.*/
        while(temp != NULL){
            if(strcmp(temp->name, new->name) == 0){
                if(((strcmp(temp->type, EX) == 0) && (strcmp(new->type, EX) != 0))
                || ((strcmp(temp->type, EX) != 0) && (strcmp(new->type, EX) == 0)))
                    return ERROR; /*Error flag indicating conflicting labels.*/
            }
            /*Move to the last label in the list.*/
            if(temp->next == NULL)
                break;
            temp = temp->next;
        }
        /*Append the new label to the end of the list.*/
        temp->next = new;
    }
    /*Success flag indicating the label was added successfully.*/
    return SUCCESS;
}


void free_label_list(Label *head){
    Label *temp;

    /*Traverse the list, freeing each node one by one.*/
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}


Boolean is_legal_label(char *name, int line){

    ignore_white_space(name);
    /*Remove the colon ':' from the end of the label (if present).*/
    if(name != NULL) {
        if (*(name + (strlen(name) - 1)) == LABEL_ID) {
            *(name + (strlen(name) - 1)) = '\0';
        }
    }

    /*Check if the label name exceeds the maximum allowed length.*/
    if(strlen(name) > LABEL_LEN) {
        PRINT_ERR(line, ERR_LABEL_LEN);
        return False;
    }

    /*Check if the label name clashes with a reserved function name.*/
    if(check_if_func(name)){
        PRINT_ERR(line, USE_FUNC_LABEL);
        return False;
    }

    /*Check if the label name is valid (contains only alphanumeric or numeric characters and the first character
     * is alphanumeric).*/
    if(!check_if_word(name)){
        PRINT_ERR(line, ERR_LABEL_NAME);
        return False;
    }
    /*If all checks pass, the label is considered legal.*/
    return True;
}
