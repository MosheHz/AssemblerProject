#include "out.h"



void print_base64(unsigned short int arr[], FILE *f, int num){
    /*Mask to extract the rightmost 6 bits.*/
    unsigned short int mask_right = MASK;
    /*Mask to extract the leftmost 6 bits(not really leftmost but leftmost fo what we need).*/
    unsigned short int mask_left = (short int)(mask_right << SHIFT_MASK);
    unsigned short int x,y;
    int i = 0, max = num;
    char base64[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K',
                     'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                     'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e',
                     'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                     'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
                     'z', '0', '1', '2', '3', '4', '5', '6', '7', '8',
                     '9','+', '/'};


    while(i < max){
        x = (unsigned short int)((arr[i] & mask_left) >> SHIFT_MASK);
        y = (unsigned short int)(arr[i] & mask_right);
        fprintf(f,"%c%c\n", base64[x], base64[y]);
        i++;
    }

}

int out(StrData* pt){
    FILE *pf = NULL;
    Label *p;
    char *ob_file_name, *ent_file_name, *ext_file_name;


    /*Create and open the object file for writing.*/
    ob_file_name = creat_new_file_name(pt->file_name, OB_TYPE);
    pf = fopen(ob_file_name, "w");
    fprintf(pf, "%d  %d\n", pt->ic, pt->dc);


    /*Print the base64-encoded instruction table and data table to the object file.*/
    print_base64(pt->table, pf, pt->ic);
    print_base64(pt->da_table, pf, pt->dc);
    fclose(pf);
    pf = NULL;

    /*Process entry labels and create the entry file if needed.*/
    p = pt->label_list;
    while (p != NULL){
        if(strcmp(p->type, EN) == 0){
            if(pf == NULL){
                ent_file_name = creat_new_file_name(pt->file_name, EXT_TYPE);
                pf = fopen(ent_file_name, "w");
            }
            fprintf(pf, "%-32s    %d\n", p->name, (p->location + OFFSET));
        }
        p = p->next;
    }
    if(pf != NULL)
        fclose(pf);
    pf = NULL;

    /*Process external labels and create the external file if needed.*/
    p = pt->tmplist;
    while (p != NULL){
        if(strcmp(p->type, EX) == 0){
            if(pf == NULL){
                ext_file_name = creat_new_file_name(pt->file_name, ENT_TYPE);
                pf = fopen(ext_file_name, "w");
            }
            fprintf(pf, "%-32s    %d\n", p->name, (p->location + OFFSET));
        }
        p = p->next;
    }
    if(pf != NULL)
        fclose(pf);


    return SUCCESS;
}


