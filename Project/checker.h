#include "head.h"
#include "error.h"
#include "util.h"


#define NON 0
#define IMME 1
#define DIRE 3
#define REGI 5
#define MAX_DATA 2047
#define MIN_DATA (-2048)
#define TOKEN_CHECKER " \n\t\r"
#define COMMA ','


/* This function check if a given string (str) exists in the provided list (list[]).
 * It takes the string to be checked and the list of strings as input.
 * Returns the index of the string in the list if found, or -1 if not found.*/
int check_item_in_list(char *str, const char *list[]);


/*This function check if a given string corresponds to a register from a predefined list.
 * It takes the string as a char pointer and returns the index of the register in the list if found, or -1 otherwise.*/
int check_reg_num(char *name);


/* This function check the type of parameter represented by the given string (param).
 * It takes the string parameter as input and returns one of the following constants:
 * - REGI: If the parameter is a valid register name.
 * - IMME: If the parameter is a valid immediate (numeric) value.
 * - DIRE: If the parameter is a valid word (directive).
 * - NON: If the parameter is NULL (no parameter).
 * Returns -1 if the parameter is not recognized as any of the above types.*/
int check_param(char *param);


/* This function check if the input line is too large (exceeds the maximum line length).
 * It takes the input line as a const char pointer and returns True if the line is too large, False otherwise.*/
Boolean check_line_to_large(char const *line);


/*This function check if there are two consecutive commas in the input line.
 * It takes the input line as a char pointer and returns True if two consecutive commas are found, False otherwise.*/
Boolean check_two_comma(char *line);

/*This function check if a given string name corresponds to a reserved directive name.
 * It takes the label name as a char pointer and returns True if the name is a reserved directive name, False otherwise.*/
Boolean check_if_directive(char *name);

/*This function check if a given string name corresponds to a reserved function name.
 * It takes the label name as a char pointer and returns True if the name is a reserved function name, False otherwise.*/
Boolean check_if_func(char *name);


/*This function check if a given name corresponds to a valid register.
 * It takes the name as a char pointer and returns True if the name corresponds to a valid register, False otherwise.*/
Boolean check_if_reg(char *name);

/* This function checks if a given string can be converted to a legal integer number within the specified range.
 * It takes a pointer to a string and returns a Boolean value indicating whether the string is a valid integer or not. */
Boolean check_if_legal_num(char *str);


/* This function check if a given string (str) is a valid word.
 *  It takes the string to be checked as input and returns True if the string is a valid word, False otherwise.*/
Boolean check_if_word(char *str);


/* This function check if a given name matches any of the provided macro names (list[]).
 * It takes the list of macro names and the string name as input and returns True if a match is found, False otherwise.*/
Boolean check_if_macro(char **list, char *name);

/* This function checks if a given string is enclosed in double quotes, indicating a string literal.
 * It takes a pointer to a string and returns a Boolean value indicating whether the string is a valid string
 * literal or not. */
Boolean check_if_string(char *str);


