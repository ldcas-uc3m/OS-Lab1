/* ---------------------------------------- */
/* Includes Section                         */
/* ---------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/* ---------------------------------------- */
/* Defines Section                          */
/* ---------------------------------------- */

#define MAX_BUFFER 1024
#define RETURN_OK     0
#define RETURN_ERROR -1

/* ---------------------------------------- */
/* Global variables                         */
/* ---------------------------------------- */
  
 

/* ---------------------------------------- */
/* Main                                     */   
/* ---------------------------------------- */
int main(int argc, char* argv[])
{
	char  buff_RX[MAX_BUFFER];           // Buffer to read the file 1024 Bytes
	char* fName = NULL;                    // Name of the File to read
	int   hFile;                           // Handle File
	int exitCode; // Code of the return of the program (RETURN_OK =0) or (RETURN_ERROR =-1)
	int nBytes;   // Auxiliary variable to read the file
	int flgRead;
	
	exitCode = RETURN_ERROR;
	
	if (argc == 2)
	  {
	
		fName = argv[1];
			
		/* Open File */
		hFile = open(fName, O_RDONLY);
		if ( hFile != -1 )              // If hFile is -1 that means that the provided file has not been found
		   {
			int mBytes;
		    // Loop to read the file
		    while ((nBytes = read(hFile, buff_RX, MAX_BUFFER )) > 0)  // A maximum of 1024 bytes from the file is copied ino the buffer in each turn
            {
		     	mBytes = write(STDOUT_FILENO, buff_RX, MAX_BUFFER);
			}

			if(nBytes == -1){
				printf("Error reading the file");
				exitCode = RETURN_ERROR;
			}

			// Close File 
			close(hFile);
			exitCode = RETURN_OK;
		}
		  
  	}
	else{
		exitCode = RETURN_ERROR;
	}

	return(exitCode);
}


