#include <stdio.h>	/*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <fcntl.h>	/*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>


int main(int argc, char *argv[])
{
	int infile;
	DIR *directory;
	struct dirent *dir;
	char currentdir[PATH_MAX];
	
	
	getcwd(currentdir, PATH_MAX);
	directory = opendir(currentdir);
	
	while((dir = readdir(directory)) != NULL){
		if(dir->d_type == DT_REG){

			infile = open(dir->d_name, O_RDONLY);

			if (infile < 0){
				return -1;
			}
			
			long position;

			position = lseek(infile, 0, SEEK_END);
			
			close(infile);
			printf("%s	%ld\n", dir->d_name, position);
		}

	}

	closedir(directory);

	return 0;
}
