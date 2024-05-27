#include "head.h"
#include "macro.h"
#include "process.h"
#include "replace.h"
#include "out.h"
#include "error.h"

#define PROCESS "\n    *************** Processing the file ***************\n"
#define END_PROCESS "      ************** End of process **************\n\n"
#define PROCESS_STOP "     *************** Process stopped **************\n\n"



/* The main function processes a series of source files provided as command-line arguments.
 * It allocates memory for the StrData structure to hold assembler data for each file.
 * The assembler function is called for each file, and if an error occurs, it is handled,
 * and memory is freed. After successful processing, the output files are generated.*/
int assembler(char *file_name, StrData *str_data);

/*Free memory associated with a StrData structure.*/
void free_StrData(StrData *str_data);
