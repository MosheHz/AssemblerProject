#include "head.h"
#include "checker.h"


#define STRING_ID ".string"
#define DATA_ID ".data"


/*This function is responsible for parsing and processing data based on the token value.
 * It can handle both string data and numeric data. */
unsigned short int* data_andler(char *token, unsigned short int *table, int *counter, int line);
