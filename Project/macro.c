#include "macro.h"


int macros_layout(StrData *str_data){
    FILE *as_file, *am_file;
    Macro *macro_list = NULL, *temp_macro;
    char line[MAX_LINE] = {0}, temp_line[MAX_LINE], *macro_name, *get, *token, *temp_name, **pinter_to_list = NULL;
    int already_put, in_flag = 0, out_flag = 0, line_counter = -1, num_of_macros = 0;

    str_data->macro_list = NULL;
    /*Open an as_file for reading the code*/
    as_file = fopen(str_data->file_name, "r+");
    if(as_file == NULL){
        PRINT(ERR_FILE_OP);
        return ERROR;
    }
    /*Changing the name to am_file.*/
    if((str_data->file_name = creat_new_file_name(str_data->file_name, AM_TYPE)) == NULL)
        return ERROR;
    /*Open an am_file for writing the modified code*/
    am_file = fopen(str_data->file_name, "w");
    if(am_file == NULL){
        PRINT(ERR_FILE_OP);
        return ERROR;
    }

    /*Read input file line by line*/
    while ((get = (fgets(line, MAX_LINE, as_file))) != NULL){
        line_counter++;

        already_put = OFF;
        strcpy(temp_line, line);
        token = strtok(temp_line, TOKEN_CHECKER);
        /*Skip empty lines and comments lines*/
        if(token == NULL || *token == COMMENT){
            continue;
        }

        if(strcmp(token, MACRO) == 0){
            temp_name = strtok(NULL, TOKEN_CHECKER);

            /*Check if the macro name is legal.*/
            if(!is_legal_macro(pinter_to_list, temp_name, line_counter)){
                error_flag = ON;
                continue;
            }

            if((macro_name = alloc_char(temp_name)) == NULL)
                break;

            /*Add the macro name to the list of macros.*/
            if((pinter_to_list = put_in_macro_arr(pinter_to_list, macro_name, num_of_macros++)) == NULL)
                break;

            out_flag = OFF;
            in_flag = ON;
            continue;
        }

        if(strcmp(token, END_MACRO) == 0) {
            in_flag = OFF;
            out_flag = ON;
            continue;
        }

        /*Process lines inside a macro definition*/
        if(in_flag){
            temp_macro = create_macro(macro_name, line);
            if(temp_macro == NULL)
                break;
            put_macro_in_list(&macro_list, temp_macro);
        }

        /*Replace macro names with their expanded code.*/
        if(out_flag){
            temp_macro = macro_list;
            while(temp_macro != NULL){
                if(strcmp(temp_macro->name, token) == 0){
                    fputs(temp_macro->line, am_file);
                    already_put = ON;
                }
                temp_macro = temp_macro->next;
            }
            if(already_put){
                continue;
            }

        }
        /*Write the line to the output file.*/
        fputs(line, am_file);
    }

    /*Close the files and free the memory.*/
    fclose(as_file);
    fclose(am_file);
    free_macro_list(macro_list);

    /*If the loop ended because of a memory allocation problem.*/
    if(get != NULL){
        return ALLOC_ERROR;
    }
    /*Update the StrData structure with the  macro list.*/
    str_data->macro_list = pinter_to_list;

    if(error_flag)
        return ERROR;

    return SUCCESS;
}



Macro* create_macro(char *macro_name, char *line){
    Macro *temp;

    /*Allocate memory for a new Macro node*/
    if((temp = (Macro *)malloc(sizeof(Macro))) == NULL){
        printf(ERR_ALLOC_MEM);
        return NULL;
    }
    /*Allocate memory for the macro name and copy it*/
    if((temp->name = alloc_char(macro_name)) == NULL)
        return NULL;
    /*Copy the provided line to the Macro node's line field*/
    strcpy(temp->line, line);
    /*Set the 'next' field to NULL since this is a new node*/
    temp->next = NULL;

    return temp; /*Return a pointer to the created Macro node*/
}


void put_macro_in_list(Macro **head, Macro *new){
    Macro *temp = *head;

    /*If the list is empty, update 'head' to point to the new node*/
    if(temp == NULL){
        temp = new;
        *head = temp;
    }
    else{
        /*Traverse the list to find the last node*/
        while(temp->next != NULL)
            temp = temp->next;

        /*Insert the new node at the end of the list*/
        temp->next = new;
    }
}

void free_macro_list(Macro *list){
    Macro *temp;

    while(list != NULL) {
        temp = list;
        list = list->next;
        free_macro(temp);
    }
}

void free_macro(Macro *p){
    free(p->name);
    free(p);
}

Boolean is_legal_macro(char **list, char *macro, int line){

    /*If something is written after the name of the macro.*/
    if((strtok(NULL, TOKEN_CHECKER)) != NULL){
        PRINT_ERR(line , EXTRA_TEX_MACRO);
        return False;
    }

    /*check if the macro name conflicts with an instruction name.*/
    if(check_if_func(macro)){
        PRINT_ERR(line, USE_FUNC_MACRO);
        return False;
    }

    /*check if the macro name conflicts with a directive name*/
    if(check_if_directive(macro)){
        PRINT_ERR(line, USE_INST_MACRO);
        return False;
    }

    /*check if the macro name conflicts with a register name.*/
    if(check_if_reg(macro)){
        PRINT_ERR(line, USE_REG_MACRO);
        return False;
    }

    /*check if the macro name conflicts with another macro name.*/
    if(check_if_macro(list, macro)){
        PRINT_ERR(line, ERR_MACRO_NAME);
        return False;
    }
    return True;

}

char** put_in_macro_arr(char **macro_arr ,char *macro_name, int num_of_elem){
    char **macro_array = macro_arr, **temp;

    /*If the macro array is initially empty, allocate memory for two elements.*/
    if(macro_array == NULL){
        if((macro_array = (char **)malloc( 2 * sizeof(char *))) == NULL){
            PRINT(ERR_LABEL_NAME);/*Error message if memory allocation fails.*/
            return NULL;
        }
    }
    /*Reallocate memory to accommodate the new element*/
    else{
        if((temp = (char **)realloc(macro_array, (num_of_elem + 2)*sizeof(char *))) == NULL){
            PRINT(ERR_LABEL_NAME);/*Error message if memory allocation fails.*/
            free(macro_array);
            return NULL;
        }
        macro_array = temp;
    }
    /*Add the new macro name to the array.*/
    *(macro_array + num_of_elem) = macro_name;
    /*Mark the end of the array with NULL.*/
    *(macro_array + (num_of_elem + 1)) = NULL;

    return macro_array;
}

