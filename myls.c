/*
@author: ldcas-uc3m
@date: 03/03/2021
*/

#include <stdio.h>		/* Header file for system call printf */
#include <unistd.h>		/* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir & closedir */
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){

	/* ---
	SETTING DIRECTORY
	--- */

	char buff[PATH_MAX]; // Buffer to save the directory
	switch (argc){
		case 1:
			/* no argument provided, use current directory */
			getcwd(buff, PATH_MAX); // note to self: on buff[n], buff serves as the pointer
			if (buff == NULL){
				printf("ERROR: Could not find current pathname.");
			}
			break;
		case 2:
			strcpy(buff, argv[1]);
			break;
		default:
			/* too many arguments */
			printf("ERROR: Too many arguments.\n");
			return -1;
	}

	/* ---
	MAIN LOOP
	--- */

	DIR *dirp = opendir(buff); // Directory pointer
	if (dirp == NULL){
		printf("ERROR: Failed to open directory");
		return -1;
	}

	struct dirent *next;
	int errno = 0; // error number "returned" from readdir(). If != 0, an error has ocurred
	while ((next = readdir(dirp)) != NULL){
		printf("%s\n", next->d_name); // using "->" instead of "." bc 'next' is a pointer
	}

	if (errno != 0){
		/* NULL has been returned, because of an error */
		printf("ERROR: Failed to read from the directory. Error No. %i", errno);
		return -1;
	}

	/* ---
	CLOSE
	--- */

	closedir(dirp);
	return 0;
}

