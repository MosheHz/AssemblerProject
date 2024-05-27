#include "replace.h"




void replace(StrData *str_data){
    Label *temp, *label;
    enum {E = 1, R};/*Constants for different types of entries.*/
    int num;

    /*Add entry locations to the "entry" labels.*/
    add_entry_location(&str_data->label_list);


    temp = str_data->tmplist;
    label = str_data->label_list;


    while(temp != NULL){

        /*Handle the case when a label is not found in the label list.*/
        if(label == NULL){
            num = atoi(temp->type);/*Extract the location for printing error.*/
            PRINT_ERR(num, NO_LAB);
            error_flag = ON;
            temp = temp->next;
            label = str_data->label_list;
            continue;
        }

        /*Replace the label with its location in the instruction table.*/
        if(strcmp(temp->name, label->name) == 0){
            if(strcmp(label->type, EX) == 0){
                strcpy(temp->type,label->type);
                str_data->table[temp->location] = E;
            }
            /*For "relocatable" labels, update the instruction table with the corresponding entry.*/
            else
                str_data->table[temp->location] = (short int)(((label->location + OFFSET) << SHIFT_R) | R);
            temp = temp->next;
            label = str_data->label_list;
            continue;
        }
        label = label->next;
    }
}


int add_entry_location(Label **pointer){
    Label *p = *pointer, *q;

    while(p != NULL){
        /*Check if the label type is "entry".*/
        if(strcmp(p->type, EN) == 0) {
            q = *pointer;
            while (q != NULL) {
                /*Find the corresponding label and update its location.*/
                if ((strcmp(p->name, q->name) == 0) && (q != p)) {
                    p->location = q->location;
                    break;
                }
                q = q->next;
            }
            /*If no corresponding entry label is found, report an error.*/
            if(q == NULL){
                PRINT_ERR(p->location, NO_ENTRY);
                error_flag = ON;
            }
        }
        p = p->next;
    }
    return SUCCESS;
}
