/* example program to use an argument vector  */
/* usage "./prog"	                              */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

struct {
    char *fname;
    char *args[5];
} cmd;

int
main(int argc, char *argv[])
{
    cmd.fname = "/usr/bin/head";
    cmd.args[0] = "head";
    cmd.args[1] = "-5";
    cmd.args[2] = "/etc/passwd";
    cmd.args[3] = NULL;

    if (fork() == 0) {
        /* child */
        execv(cmd.fname,cmd.args);
        perror(cmd.fname);
        _exit(1);
    }
    wait(NULL);
}
