/* example program using access and a list of directories	*/
/*   usage:  whence progname		*/

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *prefixes[] = {"/bin", "/usr/bin/", "/opt/local/bin", "/usr/local/sbin", NULL};
	char pathbuf[PATH_MAX + 1]; // large enough for OS max, and checked below!
	char *progname =argv[1];

	for (int i=0; prefixes[i]; ++i) {
		snprintf(pathbuf,sizeof(pathbuf), "%s/%s", prefixes[i], progname);
		printf("trying '%s'\n", pathbuf);
		if (access(pathbuf,X_OK) == 0) {
			printf("This works: '%s'\n", pathbuf);
			exit(0);
		}
	}
	printf("Not Found!\n");
	exit(-1);
}
