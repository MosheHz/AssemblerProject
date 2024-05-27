#include "instruction.h"


unsigned short int inst_checker(Function *func, Label **label, int line, int *inc, int location){
    enum {non, direct, dir_and_reg, all_kind};
    Label *lab_sours = NULL, *lab_target = NULL;
    int i = 0, result, check, param = 0, sour_lab = 1;
    unsigned short int temp, bin_code = 0;

    /*Array of supported  functions and their parameter types.*/
    Function func_arr[] = {
            {"mov", {all_kind} , {dir_and_reg}},
            {"cmp", {all_kind}, {all_kind}},
            {"add", {all_kind}, {dir_and_reg}},
            {"sub", {all_kind}, {dir_and_reg}},
            {"not", {non}, {dir_and_reg}},
            {"clr", {non}, {dir_and_reg}},
            {"lea", {direct}, {dir_and_reg}},
            {"inc", {non}, {dir_and_reg}},
            {"dec", {non}, {dir_and_reg}},
            {"jmp", {non}, {dir_and_reg}},
            {"bne", {non}, {dir_and_reg}},
            {"red", {non}, {dir_and_reg}},
            {"prn", {non}, {all_kind}},
            {"jsr", {non}, {dir_and_reg}},
            {"rts", {non}, {non}},
            {"stop", {non}, {non}},
            {NULL},
    };
    /*To see if an error occur in the source parameter so no need to check the target parameter*/
    check = error_flag;
    error_flag = OFF;

    /*Loop through the list of supported functions to find a match.*/
    while(func_arr[i].name != NULL) {
        if (strcmp(func->name, func_arr[i].name) == 0) {

            /*Generate binary code for the opcode.*/
            temp = (unsigned short int) (i);
            bin_code = (unsigned short int) (bin_code | (temp << SHIFT_OP));

            /*Check and process the source parameter.*/
            switch (result = check_param(func->source.str)) {
                case REGI:
                    if (func_arr[i].source.num != all_kind) {
                        PRINT_ERR(line, FUNC_INC_ARG);
                        error_flag = ON;
                    }
                    param = (check_reg_num(func->source.str) << SHIFT_OP);
                    break;

                case IMME:
                    if (func_arr[i].source.num != all_kind){
                        PRINT_ERR(line, FUNC_INC_ARG);
                        error_flag = ON;
                    }
                    param = atoi(func->source.str);
                    if((param < MIN_IMM) || (param > MAX_IMM)){
                        PRINT_ERR(line, NUM_OVER);
                    }
                    break;

                case DIRE:
                    if ((func_arr[i].source.num != all_kind) && (func_arr[i].source.num != direct)){
                        PRINT_ERR(line, FUNC_INC_ARG);
                        error_flag = ON;
                    }
                    /*If it's a direct address, create label and put in temp list in the StrData.*/
                    if(!is_legal_label(func->source.str, line)){
                        error_flag = ON;
                        break;
                    }
                    if((lab_sours = create_label(func->source.str)) == NULL){
                        PRINT(ERR_ALLOC_MEM);
                        return 1;
                    }
                    /*Saving the row number in an unused 'type' field, to print an error later if necessary.*/
                    sprintf(lab_sours->type, "%d", line);
                    lab_sours->location = (location + sour_lab);
                    lab_sours->next = NULL;
                    put_label_in_list(label, lab_sours);
                    break;

                case NON:
                    if (func_arr[i].source.num != non){
                        PRINT_ERR(line, FUNC_MIS_ARG);
                        error_flag = ON;
                    }
                    sour_lab--;
                    break;

                default:
                    PRINT_ERR(line, UNREC_PARAM);
                    error_flag = ON;
            }

            if(error_flag){
                free(func->source.str);
                free(func->target.str);
                break;
            }

            error_flag = check;/*Error_flag gets back it's value.*/

            /*Update binary code with source parameter information.*/
            check = result;
            temp = (unsigned short int) (result);
            bin_code = (unsigned short int) (bin_code | (temp << SHIFT_SOU));
            free(func->source.str);
            func->source.num = (param << SHIFT_DES);
            param = 0;

            /*Check and process the target parameter.*/
            switch (result = check_param(func->target.str)) {
                case IMME:
                    if (func_arr[i].target.num != all_kind){
                        PRINT_ERR(line, FUNC_INC_ARG);
                        error_flag = ON;
                    }
                    param = atoi(func->target.str);
                    if((param < MIN_IMM) || (param > MAX_IMM)){
                        PRINT_ERR(line, NUM_OVER);
                    }
                    break;

                case REGI:
                    if ((func_arr[i].target.num != all_kind) && (func_arr[i].target.num != dir_and_reg)){
                        PRINT_ERR(line, FUNC_INC_ARG);
                        error_flag = ON;
                    }
                    param = check_reg_num(func->target.str);
                    break;

                case DIRE:
                    if ((func_arr[i].target.num != all_kind) && (func_arr[i].target.num != dir_and_reg)){
                        PRINT_ERR(line, FUNC_INC_ARG);
                        error_flag = ON;
                    }
                    /*If it's a direct address, create label and put in temp list in the StrData.*/
                    if(!is_legal_label(func->target.str, line)){
                        error_flag = ON;
                        break;
                    }
                    if((lab_target = create_label(func->target.str)) == NULL){
                        PRINT_ERR(line, ERR_ALLOC_MEM);
                        return 1;
                    }
                    /*Saving the row number in an unused 'type' field, to print an error later if necessary.*/
                    sprintf(lab_target->type, "%d", line);
                    lab_target->location = (location + ++sour_lab);
                    lab_target->next = NULL;
                    put_label_in_list(label, lab_target);
                    break;

                case NON:
                    if (func_arr[i].target.num != non){
                        PRINT_ERR(line, FUNC_MIS_ARG);
                        error_flag = ON;
                    }
                    break;
                default:
                    PRINT_ERR(line, UNREC_PARAM);
                    error_flag = ON;
            }
            /*Update binary code with target parameter information.*/
            check += result;
            temp = (short int) (result);
            bin_code = (short int) (bin_code | (temp << SHIFT_DES));
            free(func->target.str);
            func->target.num = (param << SHIFT_DES);
            break;
        }
        i++;
    }
    /*Handle the case when the function is not recognized.*/
    if(func_arr[i].name == NULL){
        PRINT_ERR(line, NOT_FUNC);
        free(func->source.str);
        free(func->target.str);
        error_flag = ON;
    }
    /*Determine the instruction size increment based on the parameters.*/
    if (check != 0) {
        if (check % 2 == 0 && check / 2 != 5)
            *inc = 2;
        else
            *inc = 1;
    }
    /*Return the binary code for the instruction.*/
    return bin_code;
}


int asi_to_func(Function *pt_func, char *token, int line){
    char *comma = ",";
    int target_flag = OFF;


    /*Allocate memory for the instruction name.*/
    if ((pt_func->name = alloc_char(token)) == NULL) {
        PRINT(ERR_ALLOC_MEM);
        free(pt_func);
        return ALLOC_ERROR;
    }

    /*Check for an illegal comma at the beginning or end of the token.*/
    if((token != NULL) && ((*token == COMMA) || (*(token + (strlen(token)-1)) == COMMA))){
        PRINT_ERR(line, ILLEGAL_COMM);
        return ERROR;
    }
    /*Parse and store the source operand (if any).*/
    if ((token = strtok(NULL, comma)) != NULL) {
        /*Check if the token ends with a newline, indicating source operand is missing.*/
        if(*(token + (strlen(token) -1)) == '\n'){
            *(token + (strlen(token) -1)) = '\0';
            target_flag = ON;
        }
        ignore_white_space(token);
        /*Allocate memory for the source operand and store it. */
        if(strlen(token) > 0){
            if ((pt_func->source.str = alloc_char(token)) == NULL) {
                PRINT(ERR_ALLOC_MEM);
                free_func(pt_func);
                return ALLOC_ERROR;
            }
        }
    }else {
        pt_func->source.str = NULL;
    }

    /*Parse and store the target operand (if any).*/
    if ((token = strtok(NULL, TOKEN_CHECKER)) != NULL) {
        ignore_white_space(token);
        /*If comma appear in the end of the target operand.*/
        if(*(token + (strlen(token)-1)) == COMMA){
            free(pt_func->source.str);
            PRINT_ERR(line, ILLEGAL_COMM);
            return ERROR;
        }

        /*Allocate memory for the target operand and store it.*/
        if ((pt_func->target.str = alloc_char(token)) == NULL) {
            PRINT(ERR_ALLOC_MEM);
            free(pt_func->source.str);
            free_func(pt_func);
            return ALLOC_ERROR;
        }
    } else {
        pt_func->target.str = NULL;
    }

    /*Check for any additional text after the instruction token.*/
    if((token = strtok(NULL, TOKEN_CHECKER)) != NULL){
        PRINT_ERR(line, EXT_TEXT);
        free(pt_func->source.str);
        free(pt_func->target.str);
        return ERROR;
    }

    /*Swap source and target if source is not specified.*/
    if(target_flag){
        pt_func->target.str = pt_func->source.str;
        pt_func->source.str = NULL;
    }

    return SUCCESS;/*If there is no error in the syntax of the operands.*/
}


void free_func(Function *func){
    free(func->name);
    free(func);
}
