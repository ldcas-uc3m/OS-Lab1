#include <stdio.h>		/* Header file for system call printf */
#include <unistd.h>		/* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>

#define PATH_MAX 16  //TODO: set to a non-arbitrary number

int main(int argc, char *argv[]){

	/*
	---
	SETTING DIRECTORY
	---
	*/

	DIR *dir;
	switch (argc){
		case 0:
			// no argument provided, use current directory
			dir = getwd(dir);
			if (dir == NULL){
				printf("ERROR: Could not find current pathname.")
			}
			break;
		case 1:
			dir = argv[1];
			break;
		default:
			// too many arguments
			printf("ERROR: Too many arguments.\n");
			return -1;
	}

	//TODO: fix this shit
	int ddesc;
	struct dirent *current;
	while (ddesc = opendir(dir) != NULL){
		current = readdir(dir);
		printf("%s\n", current.d_name);
	}
	if (ddesc < 0){
		printf("ERROR: Failed to open directory.\n");
		return -1;
	}

	// struct dirent *pointer = readdir(dir);


	closedir(ddesc);
	return 0;
}

