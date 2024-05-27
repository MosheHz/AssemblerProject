

/*    Author: Moshe Heifetz.    */


/* This project is an invented assembly language assembler.
 * The program gets a files with invented assembly language code and checks the syntax.
 * If non error occur in the file the program will create an 'object' file (.ob)
 * with base 64 code representation, 'entry' file (.ent) that represent the location
 * of entry labels (use for other files if they use those labels), 'extern' file (.ext)
 * that represent the location of which the file use extern labels.
 * If an error occur the program will print an error message and continue
 * to test the rest of the code in case of error no output files will be created. */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE 82
#define LABEL_LEN 32
#define TYPE_LEN 5
#define EXIT_ERROR (-1)
#define MAX_MEM 924 /*1024 - 100 that saved for the system.*/
#define EX "extr"
#define EN "entr"



#ifndef STR
#define STR

/*This struct holds information about label.
 * Name, type(code, entry/extern, data), and location.*/
typedef struct label{
    char name[LABEL_LEN];
    char type[TYPE_LEN];
    int location;
    struct label *next;
}Label;

/* This struct holds data from file. the name of the file, two tables for instruction and data,
 * list of macro names(if any), two lists of labels directives and operands(temporary) (if any),
 * counters for instructions and data.
 * the struct helps to minimize the number of arguments sent to function.*/
typedef struct strData{
    char *file_name;
    unsigned short int table[MAX_MEM];
    unsigned short int *da_table;
    char **macro_list;
    Label *label_list;
    Label *tmplist;
    int ic;
    int dc;
}StrData;

typedef enum boolean{
    False,
    True
}Boolean;

/*An enum definition for errors and a success value returned by the function*/
enum {ALLOC_ERROR = -1, SUCCESS, ERROR};

enum {OFF, ON};
#endif

extern int error_flag;



