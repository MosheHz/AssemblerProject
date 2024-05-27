#include "head.h"
#include "checker.h"
#include "label.h"
#include "instruction.h"
#include "data.h"
#include "directive.h"
#include "error.h"


#define DATA  "data"
#define COD  "code"
#define NEW_LINE '\n'


/* This function performs the first pass of the assembly process. It reads the input file line by line, processes the directives
 * and instructions, and builds the symbol table and the data table accordingly.
 *  The function olds tow label lists the first one is for the label of directives or instructions and the second is for operands labels.
 * It updates the instruction counter (ic) and data counter (dc) in the str_data struct.
 * It takes the str_data struct pointer (str_data) as input and returns SUCCESS (0) if successful, or ALLOC_ERR (-1) in case of an error.*/
int process_file(StrData *str_data);

