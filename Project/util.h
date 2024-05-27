#include "head.h"
#include "error.h"


#define AS_TYPE ".as"
#define MAX_TYPE_LEN 5

/*macro of print function.*/
#define PRINT(X) fprintf(stderr, (X))

/* This function removes leading and trailing white spaces from a string.
 * It takes a pointer to a character string and modifies it in place by removing leading and trailing white spaces.
 * If there are newline character, newline character are preserved at the end of the string.*/
void ignore_white_space(char *str);


/* This function allocate memory for a new string and copy the content of the provided string (str) to the new one.
 * It takes the source string (str) as input and returns a pointer to the newly allocated string (p).
 * If memory allocation fails, it returns NULL.*/
char* alloc_char(char *str);


/* This function creates a new file name by replacing the extension of an existing file name with a new extension.
 * It takes the old file name and the new extension type as input and returns the new file name.*/
char* creat_new_file_name(char *old, char *type);


/* This function creates a new file name with the ".as" extension by appending it to the input name.
 * It takes the base file name (without extension) and returns a new dynamically allocated character string
 * representing the new file name with the ".as" extension.*/
char* creat_as_file(char *name);


/* This function frees an array of pointers and the memory they point to.
 * It takes an array of character pointers and frees both the array and the memory pointed to by the pointers.*/
void free_arr_of_pointers(char **arr);

/* This function sets all elements of the given character buffer to the null
 * character ('\0'), effectively clearing its content.*/
void clear_buff(char *line);
