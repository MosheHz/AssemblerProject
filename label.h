#include "head.h"
#include "checker.h"
#include "error.h"


#define LABEL_ID ':'
#define NO_LABEL " "


/* This function create a new Label node and initialize it with the given name.
 * It takes the name of the label as input and returns a pointer to the newly created Label node.
 * If memory allocation fails, it returns NULL.
 * If the name is NULL, an empty label name is assigned to the node.*/
Label* create_label(char *name);

/* This function adds a new label to a linked list of labels.
 * It takes a pointer to the head of the label list and a pointer to the new label to be added.
 * It returns a success flag indicating whether the operation was successful or not. */
int put_label_in_list(Label **head, Label *new);

/*This function free the memory allocated for the entire label list.
 * It takes the head of the label list as input and frees all the nodes in the list.*/
void free_label_list(Label *head);

/* This function check if a given label name is legal.
 * It takes the label name and the line number (for error reporting) as input.
 * It performs several checks on the label name and reports errors if any are found.
 * Returns True if the label is legal, False otherwise.*/
Boolean is_legal_label(char *name, int line);

