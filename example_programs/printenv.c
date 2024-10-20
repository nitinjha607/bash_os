#include <stdio.h>
#include <stdlib.h>

int
main(
    int argc,
    char *argv[],
    char *envp[])		/* your environment! */
{
    int i;

    for (i=0; envp[i]; ++i)
	    printf("ENV[%d]: '%s'\n", i, envp[i]);

    exit(0);
}
