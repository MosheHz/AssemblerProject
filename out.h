#include "head.h"
#include "util.h"


#define OB_TYPE "ob"
#define EXT_TYPE "ent"
#define ENT_TYPE "ext"
#define OFFSET 100
#define MASK 63
#define SHIFT_MASK 6

/* This function prints a given array of unsigned short integers as base64-encoded characters to a specified file.
 * It uses bit manipulation to extract two base64 characters from each unsigned short integer in the array.
 * The characters are written to the file with newlines after each pair.*/
void print_base64(unsigned short int arr[], FILE *f, int num);


/* This function generates output files for the assembled program.
 * It takes a pointer to a StrData structure containing the assembled data and labels.
 * It creates and writes to the object file, entry file, and external file as needed.
 * It returns SUCCESS (0) on success.*/
int out(StrData * pt);