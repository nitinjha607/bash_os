


#define MAX_ARGS 500
#include <stdbool.h>

/* This is the definition of a command */
struct command {
    char *command;
    int argc;
    char *argv[MAX_ARGS];
    char *infile;
    char *outfile;
    char *errfile;

    int output_append;		/* boolean: append stdout? */
    int error_append;		/* boolean: append stderr? */

    struct command *next;
    struct redirs *redirs; /* pointer to redirection*/
};


/* externals */
extern int yydebug;
extern int debug;
extern int lines;  // defined and updated by parser, used by bash.cc
extern bool error_reported; //flag for error debug

/* you should use THIS routine instead of malloc */
void *MallocZ(int numbytes);

/* global routine decls */
void doline(struct command *pass);
int yyparse(void);