#include "head.h"
#include "label.h"


#define OFFSET 100
#define SHIFT_R 2


/* This function replaces the label placeholders in the instruction table with
 * their corresponding locations or "01" if extern. It takes a pointer to a StrData struct containing
 * the instruction table, label list, and other relevant data. It iterates through
 * the temporary list of labels and the label list, updating the instruction table
 * with the correct values. If a label is not found, an error is printed. */
void replace(StrData *str_data);


/* This function adds entry locations to the "entry" labels in the label list.
 * It updates the locations of labels that have corresponding "entry" entries.
 * The function takes a pointer to a Label pointer, which represents the label list.
 * It returns 0 on success, or an error flag value otherwise. */
int add_entry_location(Label **pointer);
