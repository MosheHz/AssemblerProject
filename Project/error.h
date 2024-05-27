
/*Macro for printing error message.*/
#define PRINT_ERR(X, S) fprintf(stderr, "In line %d: %s", (X), (S))

#define ERR_FILE_OP "Error occurred while trying to open file.\n"
#define ERR_ALLOC_MEM "An error occurred while attempting to allocate memory.\n"
#define FULL_MEM "Error, the memory has reached full capacity.\n"
#define ERR_LINE_LEN "Error, The length of line is to large.\n"
#define TOW_CONS_COMMAS "Error, there art tow consecutive commas.\n"
#define NOT_NUM "Error, not a legal number.\n"
#define NOT_STRING "Error, illegal string.\n"
#define EXT_TEXT "Error, extra text after instruction.\n"
#define ILLEGAL_COMM  "Error, illegal comma.\n"
#define NUM_OVER "Warning, number value overflow.\n"
#define MISS_DATA "Error, missing data or string.\n"
#define NO_ENTRY "Error, no such entry in this file.\n"
#define NO_LAB "Error, no such label in this file.\n"

#define USE_FUNC_LABEL "Error, cannot use the name of an existing instruction for label.\n"
#define ERR_LABEL_NAME "Error, illegal name for label.\n"
#define WAR_NO_LAB "Warning, missing label.\n"
#define WAR_NO_NEED_LAB "Warning, redundant label.\n"
#define ERR_LABEL_LEN "Error, the length of the label name is too large.\n"
#define CONF_TYP_LAB "Error, conflict types of label.\n"
#define EMP_LAB "Error, empty label.\n"

#define UNREC_PARAM "Error, unrecognized parameter.\n"
#define NOT_FUNC "Error, unrecognized instruction.\n"
#define FUNC_INC_ARG "Error, incompatible arguments for this instruction.\n"
#define FUNC_MIS_ARG "Error, missing arguments\n"

#define ERR_MACRO_NAME "Error, the name is already used as macro name.\n"
#define EXTRA_TEX_MACRO "Error, extra text after macro name.\n"
#define USE_FUNC_MACRO "Error, cannot use the name of an existing instruction for macro.\n"
#define USE_REG_MACRO "Error, cannot use the name of an existing register for macro.\n"
#define USE_INST_MACRO "Error, cannot use the name of an existing directive for macro.\n"
