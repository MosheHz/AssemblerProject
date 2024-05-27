#include "head.h"
#include "checker.h"
#include "error.h"
#include "util.h"



#define MACRO "mcro"
#define END_MACRO "endmcro"
#define COMMENT ';'
#define AM_TYPE "am"


typedef struct macro{
    char *name;
    char line[MAX_LINE];
    struct macro *next;
}Macro;


/* This function process macros layout in the input file and create a new output file with macros expanded.
 * It takes the pointer to the strData structure (str_data) as input.
 *  Returns SUCCESS (0) on success, ALLOC_ERR (-1) on failure because memory allocation error, and ERROR (1) on failure
 *  because file opening error.*/
int macros_layout(StrData *str_data);

/* This function create a new Macro node and initialize it with the given macro name and line of code.
 * It takes the macro name (macro_name) and the line of code (line) as inputs and returns a pointer to the newly created Macro node.
 * If memory allocation fails, it returns NULL.*/
Macro* create_macro(char *macro_name, char *line);

/* This function insert a new Macro node into the macro list.
 * It takes a double pointer to the head of the macro list (head) and the new macro node to be inserted (new).
 * If the list is empty, the new macro node becomes the head.
 * Otherwise, the new macro node is appended to the end of the list.*/
void put_macro_in_list(Macro **head, Macro *new);

/* this function add a macro name to the array of macro names (pinter_to_list).
 * It takes the array of macro names (macro_arr), the macro name to be added (macro_name),
 * and the number of elements in the array (num_of_elem) as inputs.
 * If the macro_arr is NULL, it allocates memory for the first element and returns a pointer to it.
 * If the macro_arr is not NULL, it reallocates memory for an additional element and adds the macro_name to the end of the array.
 * It returns a pointer to the updated array.
 * If memory allocation fails, it returns NULL.*/
char** put_in_macro_arr(char **macro_arr ,char *macro_name, int num_of_elem);

/* this function check if a given macro name is legal.
 * It takes the macro name (macro) and the line number (for error reporting) as input.
 * It performs several checks on the macro name and reports errors if any are found.
 * Returns True if the macro name is legal, False otherwise.*/
Boolean is_legal_macro(char **list, char *macro, int line);

/*this function free the memory allocated for a single Macro node.*/
void free_macro(Macro *list);

/* This function free the memory allocated for the entire macro list.
 * It takes the head of the macro list as input and frees all the nodes in the list.*/
void free_macro_list(Macro *list);
