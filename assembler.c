#include "assembler.h"



/*Defining an extern s so that all files can access them.*/
int error_flag = OFF;


int main(int argc, char *argv[]){
    StrData *str_data = NULL;
    int checker;

    /*Loop through command-line arguments*/
    while ((argc--) > 1) {

        /*Allocate memory for StrData structure*/
        if((str_data = (StrData *)(calloc(1,sizeof(StrData)))) == NULL){
            PRINT(ERR_ALLOC_MEM);
            exit(EXIT_ERROR);
        }

        /*Call the assembler function to process the input file*/
        checker = assembler(*++argv, str_data);

        /*Remove the temporary file created during processing*/
        remove(str_data->file_name);
        /*Handle errors and clean up memory*/
        if (checker != SUCCESS){
            free_StrData(str_data);
            if(checker == ALLOC_ERROR)
                exit(EXIT_ERROR);
            PRINT(PROCESS_STOP);
            continue;
        }

        /*Printing a message that the process ended.*/
        PRINT(END_PROCESS);

        /*Call the function that responsible for the output files.*/
        out(str_data);
        free_StrData(str_data);
    }
    return 0;
}


int assembler(char *file_name, StrData *str_data){
    int checker;

    /*Reset error_flag and create output file*/
    error_flag = OFF;
    str_data->file_name = creat_as_file(file_name);
    PRINT(PROCESS);

    /*Call macros_layout to process macros*/
    checker = macros_layout(str_data);
    if(checker != SUCCESS)
        return checker;

    /*Process the input file*/
    checker = process_file(str_data);
    if(checker != SUCCESS)
        return checker;

    /*Replace the values of the instruction table by the location of the labels.*/
    replace(str_data);

    return error_flag;
}


/*Free memory associated with StrData */
void free_StrData(StrData *str_data){
    free(str_data->file_name);
    free_arr_of_pointers(str_data->macro_list);
    free(str_data->da_table);
    free_label_list(str_data->label_list);
    free_label_list(str_data->tmplist);
    free(str_data);
}
