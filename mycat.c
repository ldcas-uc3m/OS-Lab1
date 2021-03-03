
/* ---------------------------------------- */
/* Includes Section                         */
/* ---------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/* ---------------------------------------- */
/* Defines Section                          */
/* ---------------------------------------- */

#define MAX_BUFFER 1024
#define RETURN_OK     0
#define RETURN_ERROR -1

/* ---------------------------------------- */
/* Global variables                         */
/* ---------------------------------------- */
  
char  buff_RX[MAX_BUFFER+1];           // Buffer to read the file 1024 Bytes, plus 1 for the string end
char* fName = NULL;                    // Name of the File to read
int   hFile;                           // Handle File 

/* ---------------------------------------- */
/* Main                                     */   
/* ---------------------------------------- */
int main(int argc, char* argv[])
{
	int exitCode; // Code of the return of the program (RETURN_OK =0) or (RETURN_ERROR =-1)
	int nBytes;   // Auxiliary variable to read the file
	int flgRead;
	
	exitCode = RETURN_ERROR;
	
	if (argc < 2)
	  {
		printf("Error, an enter file must be provided\n");
		printf("Usage: ./mycat <path_input_file>\n");
	  }
   else
	  {
		fName = argv[1];

		printf("Open file: %s...\n\n", fName);
			
		/* Open File */
		hFile = open(fName, O_RDONLY);
		if ( hFile!=-1 )              // If hFile is -1 that means that the provided file has not been found
		   {
		     // Loop to read the file
	         
		     while ((nBytes = read(hFile, buff_RX,MAX_BUFFER ))!=0)  // A maximum of 1024 bytes from the file is copied ino the buffer in each turn
                   {
		     	     buff_RX[nBytes] = '\0';  // A character zero is added at the end of the buffer to be able to print it as a string
       	     	     printf("%s", buff_RX);
			       }

				 // Close File 
				 printf("\n\nClose file.\n");
				 close(hFile);
				 exitCode = RETURN_OK;
			 }
		  
  	  }

	return(exitCode);
}


