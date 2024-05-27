#include "data.h"


unsigned short int* data_andler(char *token, unsigned short int *table, int *counter, int line){
    char *comma = ",\n", *end_line = "\n";
    unsigned short int *temp_table = NULL, num;
    int i;

    /*Check if 'table' is NULL, and if so, allocate memory for it.*/
    if(table == NULL){
        /*Memory allocation failed; print an error message and return NULL.*/
        if((table = (unsigned short int*)malloc(2 * sizeof(unsigned short int))) == NULL){
            PRINT(ERR_ALLOC_MEM);
            return NULL;
        }
    }
    /*Check if the token indicates string data.*/
    if ((strcmp(token, STRING_ID) == 0)) {

        /*check of null and if you have two "" and to print warning if no data*/
        if((token = strtok(NULL, end_line)) != NULL){
            if(!check_if_string(token)){
                PRINT_ERR(line, NOT_STRING);
                error_flag = ON;
                return table;
            }
            /*Reallocate memory for 'temp_table' to accommodate the string data.*/
            temp_table = (unsigned short int *) realloc(table, (((*counter + (strlen(token))) * sizeof(unsigned short int))));
            if (temp_table == NULL) {
                /*Memory reallocation failed; print an error message, free 'table', and return NULL.*/
                PRINT(ERR_ALLOC_MEM);
                free(table);
                return NULL;
            }

            /* Copy each character of the string data (excluding double quotes) to 'temp_table'.*/
            for (i = 1; i < strlen(token) - 1; i++) {
                *(temp_table + (*counter)++) = (unsigned short int)(*(token + i) | 0);
            }
            /*Append a null-terminator to the end of the string.*/
            *(temp_table + (*counter)++) = 0;
        }

    }

    /*Check if the token indicates numeric data*/
    else{

        while ((token = strtok(NULL, comma)) != NULL) {


            /*Check if the current token is a legal numeric value.*/
            if (!check_if_legal_num(token)) {
                /*If not legal, print an error message and set the 'error_flag'.*/
                PRINT_ERR(line, NOT_NUM);
                error_flag = ON;
                return table;
            }
            num = atoi(token);/*Convert the token to a short integer and store it in 'num'.*/

            /*Reallocate memory for 'temp_table' to accommodate the new numeric value.*/
            temp_table = (unsigned short int *) realloc(table, (((*counter) + 2) * sizeof(unsigned short int)));
            if (temp_table == NULL) {
                /*Memory reallocation failed; print an error message, free 'p', and return NULL.*/
                PRINT(ERR_ALLOC_MEM);
                free(table);
                return NULL;
            }
            /*Store the numeric value in 'temp_table'.*/
            *(temp_table + (*counter)++) = num;
            table = temp_table;/*Update 'p' to point to the newly reallocated memory.*/
        }
    }
    if(temp_table == NULL){
        PRINT_ERR(line, MISS_DATA);
        error_flag = ON;
        return table;
    }
    /*Return the modified or newly allocated memory for 'table'.*/
    return temp_table;
}
