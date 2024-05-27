#include "util.h"


void ignore_white_space(char *str){
    int i, j = 0;

    /*Check if the input string is NULL. If it is, return immediately without making any changes.*/
    if(str == NULL)
        return;

    /*Removing leading white spaces from the beginning of the string.*/
    for(i = 0; i < strlen(str); i++){
        if(!isspace(*(str + i)))
            break;
    }
    /*If there are leading white spaces, shift the characters to remove them.*/
    for(; (i != 0) && (i < strlen(str)); i++){
        *(str + j++) = *(str + i); /*Shift characters to the beginning of the string.*/
        *(str + i) = ' '; /*Replace the original character with a space.*/
    }

    /*Removing trailing white spaces from the end of the string, while keeping newlines.*/
    for(i = (int)(strlen(str) - 1); i >= 0; i--){
        if((!isspace(*(str + i))) && (*(str + i) != '\r'))
            break;
    }
    /*Terminate the string after the last non-space character.*/
    *(str + ++i) = '\0';
}


char* alloc_char(char *str) {
    char *p;
    if ((p = (char*)malloc((strlen(str) + 1) * sizeof(char))) == NULL) {
        PRINT(ERR_ALLOC_MEM);
        return NULL;
    }
    strcpy(p, str);
    return p;
}



char* creat_new_file_name(char *old, char *type){
    int i;
    char *new;

    /*Removing the existing extension from the old file name.*/
    for(i = 0; old[i++] != '.';);
    for(; i < strlen(old); i++){
        *(old + i) = '\0';
    }
    /*Concatenating the new extension to the old file name to create the new file name.*/
    new = strcat(old, type);
    return new;
}


char* creat_as_file(char *name){
    char *new_file;

    /*Allocate memory for the new file name.*/
    if((new_file = malloc((strlen(name) + MAX_TYPE_LEN) * sizeof(char ))) == NULL){
        return NULL;
    }

    /*Copy the base name to the new file name.*/
    strcpy(new_file, name);
    /*Append the ".as" extension to the new file name.*/
    strcat(new_file, AS_TYPE);

    /*Return the new file name with the ".as" extension.*/
    return new_file;
}

void free_arr_of_pointers(char **arr){
    int i;

    if(arr != NULL){
        for(i = 0; (*(arr + i)) != NULL; i++){
            free(*(arr + i));
        }
    }
    free(arr);


}

void clear_buff(char *line){
    int i;

    /*Iterate through each element of the buffer and set it to the null character*/
    for(i = 0; i < MAX_LINE; i++)
        *(line + i) = '\0';
}
