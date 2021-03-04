#include <stdio.h>	/*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>	/*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>

#define PATH_MAX 255

int main(int argc, char *argv[])
{
	int infile;
	DIR *directory;
	struct dirent *dir;
	char currentdir[PATH_MAX];
	
	/*Get the current directory in currentdir*/
	getcwd(currentdir, PATH_MAX);
	/*Open currentdir*/
	directory = opendir(currentdir);
	
	/*Read what is in the directory*/
	while((dir = readdir(directory)) != NULL){
		
		/*If it is a file execute the if statements*/
		if(dir->d_type == DT_REG){
			
			/*Open the file*/
			infile = open(dir->d_name, O_RDONLY);
			
			/*Error when openning the file*/
			if (infile < 0){
				return -1;
			}
			
			/*Get the offset of the file*/
			off_t offset = lseek(infile, 0, SEEK_END);
			
			/*Close file*/
			close(infile);
			
			/*Print the file name and the offset separated by a tab*/
			printf("%s	%ld\n", dir->d_name, offset);
		}

	}

	/*Close directory*/
	closedir(directory);

	return 0;
}
