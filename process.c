#include "process.h"



int process_file(StrData *str_data){
    FILE *fp;
    Label *label_list = NULL, *temp_label;
    Function *pt_func;
    unsigned short int *data_table = NULL, *temp_data_table = NULL, num;
    char line[MAX_LINE] = {0}, *token;
    int ic = 0, dc = 0, inc , label = OFF, line_counter = -1, checker, line_dump = OFF;


    str_data->tmplist = NULL;
    str_data->label_list = NULL;
    str_data->da_table = NULL;

    /*Open the input file for reading.*/
    if((fp = fopen(str_data->file_name, "r")) == NULL) {
        PRINT(ERR_FILE_OP);
        return ERROR;
    }

    /*Read each line from the input file.*/
    while(fgets(line, MAX_LINE, fp) != NULL) {

        line_counter++;
        inc = 0;

        /*Check if the memory is full (ic + dc exceeds MAX_MEM).*/
        if((ic + dc) > MAX_MEM){
            PRINT(FULL_MEM);
            break;
        }

        /*Check line length*/
        if((line_dump) || (check_line_to_large(line))){
            if(line_dump){
                line_counter--;
                if(strchr(line, NEW_LINE) != NULL){
                    line_dump = OFF; /*Clear line_dump flag when newline encountered.*/
                }
                clear_buff(line); /*Clear the line buffer.*/
                continue;
            }
            /*Print error message for line length.*/
            PRINT_ERR(line_counter, ERR_LINE_LEN);
            /*Set error_flag and line_dump flags.*/
            error_flag = line_dump = ON;
            clear_buff(line); /*Clear the line buffer.*/
            continue;
        }

        /*Check for two consecutive commas.*/
        if(check_two_comma(line)){
            PRINT_ERR(line_counter, TOW_CONS_COMMAS);
            error_flag = ON;
            continue;
        }

        token = strtok(line, TOKEN_CHECKER);/*Tokenize the line.*/

        /*Check if the token is label.*/
        if (*(token + (int)strlen(token) - 1) == LABEL_ID) {

            /* Check if the label is legal, if not, set the 'error_flag'.*/
            if(!is_legal_label(token, line_counter)){
                error_flag = ON;
                continue;
            }
            /*Check if the label name conflicts with a macro name from the macro_list.*/
            if((check_if_macro(str_data->macro_list, token))){
                PRINT_ERR(line_counter, ERR_MACRO_NAME);
                error_flag = ON;
                continue;
            }
            /*Create a new Label object for the token.*/
            temp_label = create_label(token);
            if (temp_label == NULL)
                return ALLOC_ERROR;
            label = ON;/*Indicate that there is a label to put in list.*/

            token = strtok(NULL, TOKEN_CHECKER);/*continue to the next word in the line.*/
            if(token == NULL){
                PRINT_ERR(line_counter, EMP_LAB);
                error_flag =ON;
                continue;
            }
        }

        /*Check if the line contains a STRING or DATA directive.*/
        if ((strcmp(token, STRING_ID) == 0) || (strcmp(token, DATA_ID) == 0)) {

            /*If there is no label before the directive, add an empty label and print a warning.*/
            if (!label) {
                PRINT_ERR(line_counter, WAR_NO_LAB);
                temp_label = create_label(NULL);
                if (temp_label == NULL)
                    return ALLOC_ERROR;
                label = ON;/*Indicate that there is a label to put in list.*/
            }

            /*Set the label type as DATA.*/
            strcpy(temp_label->type, DATA);
            temp_label->location = dc;

            /*Process the data directive and update the data_table and dc.*/
            temp_data_table = data_andler(token, data_table, &dc, line_counter);
            if(temp_data_table == NULL){
                free(temp_label);
                return ALLOC_ERROR;
            }
            data_table = temp_data_table;
        }

        /*Check if the line contains an ENTRY or EXTERN directive.*/
        else if ((strcmp(token, ENTRY_ID) == 0) || (strcmp(token, EXTERN_ID) == 0)) {

            /*If there is a label before the directive, print a warning and free the label.*/
            if (label) {
                PRINT_ERR(line_counter, WAR_NO_NEED_LAB);
                free(temp_label);
            }

            /*Process the ENTRY or EXTERN directive and update the label_list.*/
            temp_label = dire_andler(token, line_counter);
            if (temp_label == NULL)
                return ALLOC_ERROR;
            label = ON;/*Indicate that there is a label to put in list.*/


        }
        else{/*Process the instruction.*/
            if (label) {
                /* If there is a label before the instruction, set the label type as CODE and update its location.*/
                strcpy(temp_label->type, COD);
                temp_label->location = ic;
            }
            /*Allocate memory for the Function structure.*/
            if ((pt_func = (Function*)calloc(1, sizeof(Function))) == NULL) {
                return ALLOC_ERROR;
            }
            /*Convert the instruction token into a Function struct.*/
            checker = asi_to_func(pt_func, token, line_counter);
            /*If no error occurred*/
            if(checker == SUCCESS) {

                /*Validate the instruction and encode it into the instruction table (ptf->table).*/
                num = inst_checker(pt_func, &str_data->tmplist, line_counter, &inc, ic);

                if (num == ERROR) {
                    free_func(pt_func);
                    return ALLOC_ERROR;
                }
                str_data->table[ic++] = num;
                if (inc > 0) {/*Putting the values in the instruction table*/
                    if (inc == 1)
                        str_data->table[ic++] = (unsigned short int) (pt_func->source.num | pt_func->target.num);
                    else {
                        str_data->table[ic++] = (unsigned short int) (pt_func->source.num);
                        str_data->table[ic++] = (unsigned short int) (pt_func->target.num);
                    }
                }
            }
            if(checker)
                error_flag = ON;
            if(checker == ALLOC_ERROR){
                if(label)
                    free(temp_label);
                return ALLOC_ERROR;
            }
            /*Free the Function struct after processing the instruction.*/
            free_func(pt_func);
        }
        if(label){
            /*Add the label to the label_list and reset the label flag.*/
            if(put_label_in_list(&label_list, temp_label) == ERROR){
                free(temp_label);
                temp_label = NULL;
                PRINT_ERR(line_counter, CONF_TYP_LAB);
                error_flag = ON;
            }
            label = OFF;/*Indicate that there is no label to put in list.*/
        }
    }
    fclose(fp);
    /*Update the locations of DATA type labels in the label_list.*/
    temp_label = label_list;
    while(temp_label != NULL){
        if(strcmp(temp_label->type, DATA) == 0)
            temp_label->location += ic;
        temp_label = temp_label->next;
    }

    /* Update the str_data struct with the results of the first pass.*/
    str_data->ic = ic;
    str_data->dc = dc;
    str_data->label_list = label_list;
    str_data->da_table = data_table;
    return SUCCESS;
}
