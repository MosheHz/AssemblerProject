#include "head.h"
#include "label.h"
#include "checker.h"

#define SHIFT_OP 5
#define SHIFT_SOU 9
#define SHIFT_DES 2
#define MAX_IMM 511
#define MIN_IMM (-512)


typedef union data{
    int num;
    char* str;
}Data;

typedef struct instruction{
    char *name;
    Data source;
    Data target;
}Function;


/* This function checks the validity of the instruction and generates the binary code for it.
 * if there is a labels in the operand, will store them in a temp label list in the strData.
 * It takes the parsed Function, an array of Label pointers, the current line number,
 * the instruction size increment (output parameter), and the current memory location.
 * Returns the binary representation of the instruction. */
unsigned short int inst_checker(Function *func, Label **label, int line, int *inc, int location);


/*This function frees the memory allocated for the Function structure.*/
void free_func(Function *func);

/* This function converts an assembly instruction (tokenized) into a Function struct.
 * It takes a pointer to the Function struct to populate, the token containing the
 * instruction, and the line number. It returns 0 on success and 1 or -1 on failure.
 * If the function returns 1, an error occurred due to an illegal comma placement or unexpected text is present.
 * If it returns -1, an error occurred during memory allocation. */
int asi_to_func(Function *pt_func, char *token, int line);
