#include "checker.h"




Boolean check_line_to_large(char const *line){

    /*Check if the character at the maximum line length is not a newline or null terminator.*/
    if(line[MAX_LINE - 2] != '\n' && line[MAX_LINE - 2] != '\0'){
        return True;
    }
    return False;
}


Boolean check_two_comma(char *line){
    int i, j = 0;

    for(i = 0; line[i] != '\n'; i++){
        if(!(isspace(line[i]))){
            if((line[i] == COMMA) && (line[j] == COMMA)){
                return True;
            }
            j = i;
        }
    }
    return False;
}


int check_item_in_list(char *str, char const *list[]){
    int i;
    for(i = 0; list[i] != NULL; i++){
        if(strcmp(str, list[i]) == 0)
            return i;
    }
    return -1;
}


Boolean check_if_func(char *name){
    const char *func_arr[] = {"mov","cmd","add","sub","not","clr","lea","inc","dec",
                              "jmp","bnq","red","prm","jsr","rts","stop", NULL};

    if(check_item_in_list(name, func_arr) != -1){
        return True;
    }
    return False;
}

Boolean check_if_directive(char *name){
    const char *directive[] = {".extern", ".entry", ".data", ".string", NULL};

    if(check_item_in_list(name, directive) != -1){
        return True;
    }
    return False;
}

int check_reg_num(char *name){
    const char *reg_arr[] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7", NULL};
    int i;
    i = check_item_in_list(name, reg_arr);
    return i;
}


Boolean check_if_reg(char *name){
    if(check_reg_num(name) != -1)
        return True;
    return False;
}


Boolean check_if_legal_num(char *str){
    int integer;
    double num;
    char *checker;

    ignore_white_space(str);

    /*Convert the string to a floating-point number using strtod and store the result in 'num'.
     *The 'checker' pointer will be set to the character that caused the conversion to stop.*/
    num = strtod(str, &checker);

    /*If the 'checker' is not pointing to the end of the string ('\0'), the conversion was not successful,
     *indicating that the string is not a valid number. Return False.*/
    if(*checker != '\0')
        return False;

    /*Convert the 'num' to an integer to compare it with the original 'num'.
     *If they are different, the string represents a floating-point number and not a valid integer. */
    integer = (int)num;
    if(integer != num)
        return False;

    /*Check if the integer falls within the valid range for data values.
     *If it's outside the range, return False.*/
    if((integer > MAX_DATA) || (integer < MIN_DATA))
        return False;

    /*Return True if the string represents a valid integer within the specified range.*/
    return True;
}


Boolean check_if_word(char *str){
    int i;

    /*Check if the first character of the string is not an alphabetical character (letter).
     *If it's not, the string does not represent a valid word. Return False.*/
    if(!isalpha(*str))
        return False;

    /*Loop through the rest of the characters in the string starting from the second character.
     *Check if each character is alphanumeric (either a letter or a digit).
     *If any character is not alphanumeric, the string is not a valid word. Return False.*/
    for(i = 1; i < strlen(str); i++){
        if(!isalnum(*(str + i)))
            return False;
    }
    /*Return True if the string represents a valid word according to the criteria.*/
    return True;
}


int check_param(char *param){

    if(param == NULL)
        return NON;

    if(check_if_reg(param))
        return REGI;

    if(check_if_legal_num(param))
        return IMME;

    if(check_if_word(param))
        return DIRE;

    return -1;
}


Boolean check_if_macro(char **list, char *str){
    int i;

    if(list == NULL)
        return False;

    for(i = 0; (*(list + i) != NULL); i++){
        if(strcmp(*(list + i), str) == 0){
            return True;
        }
    }
    return False;
}


Boolean check_if_string(char *str){

    ignore_white_space(str);

    /*Check if the first and last characters of the string are double quotes.*/
    if((*str != '\"') || (*(str + (strlen(str) - 1)) != '\"'))
        return False; /*Return False if the string is not properly enclosed in double quotes.*/

    /*Return True if the string is a valid string literal.*/
    return True;
}
