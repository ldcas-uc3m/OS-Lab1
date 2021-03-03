/*
@author: ldcas-uc3m
@date: 03/03/2021
*/

#include <stdio.h>		/* Header file for system call printf */
#include <unistd.h>		/* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>

#define PATH_MAX 256  //TODO: set to a non-arbitrary number

int main(int argc, char *argv[]){ // TODO: Test & fix this shit

	/* ---
	SETTING DIRECTORY
	--- */

	char buff[PATH_MAX]; // Buffer to save the directory
	DIR *dirp; // Main directory pointer
	switch (argc){
		case 0:
			// no argument provided, use current directory
			dirp = getcwd(&buff, PATH_MAX); 
			if (dirp == NULL){
				printf("ERROR: Could not find current pathname.");
			}
			break;
		case 1:
			dirp = strcpy(buff, argv[1]);
			break;
		default:
			// too many arguments
			printf("ERROR: Too many arguments.\n");
			return -1;
	}

	/* ---
	MAIN LOOP
	--- */

	DIR *ddesc = opendir(dirp); // Directory descriptor
	if (ddesc == NULL){
		printf("ERROR: Failed to open directory");
		return -1;
	}

	struct dirent *next;
	errno_t errno = 0; // error number "returned" from readdir(). If it's != 0, an error has ocurred
	while (next = readdir(dirp) != NULL){
		printf("%s\n", next->d_name); // using "->" instead of "." bc 'next' is a pointer
		// TODO: add type?
	}

	if (errno != 0){
		// NULL has been returned, because of an error
		printf("ERROR: Failed to read from the directory. Error No. %i", errno);
		return -1;
	}

	/* ---
	CLOSE
	--- */

	closedir(ddesc);
	return 0;
}

