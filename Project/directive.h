#include "head.h"
#include "label.h"
#include "checker.h"
#include "error.h"


#define LEN 8
#define EXTERN_ID ".extern"
#define ENTRY_ID ".entry"


/* This function takes a string representing a directive and its associated
 * line number and creates Label objects for each token in the string. The
 * created Label objects are then linked together into a linked list and
 * returned as the head of the list. */
Label* dire_andler(char *str, int line);
