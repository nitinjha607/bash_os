/* 
 * putenv.c - just a simple test
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int
main(
    int argc,
    char *argv[])
{
    putenv("FUNCLASS=4420");

    printf("This is a fun class: \n");
    execl("/usr/bin/printenv","printenv","FUNCLASS",NULL);
}

