# OS-Lab1: System calls

## Lab Statement

This lab allows the student to familiarize with Operating System calls (specially related to
the file system management) following the POSIX standard. Unix allows you to make calls
directly to the Operating System from a program implemented in a high level language, in
particular, C language.<br/>
Most of input/output (I/O) operations in Unix can be done using uniquely five calls:
open, read, write, lseek and close.<br/>
For the Operating System kernel, all files opened are identified using file descriptors. A
file descriptor is a non negative integer. When we open a file that already exists, the kernel
returns a file descriptor to the process. When we want to read or write from/to a file, we
identify the file with the file descriptor that was returned by the open call.
Each open file has a current read/write position ("current file offset"). It is represented
by a non negative integer that measures the number of bytes from the beginning of the file.
The read and write operations normally start at the current position and create an increment in
that position equal to the number of bytes read or written. By default, this position is
initialized to 0 when a file is opened, unless the option O_APPEND is specified. The current
position (current_offset) of an open file can be changed explicitly using the system call
lseek.<br/>
To manipulate directories, you can use the system calls opendir, readdir y closedir. An
open directory is identified with a directory descriptor, which is a pointer of type DIR (DIR*).
When we open a directory with opendir, the kernel returns a directory descriptor from which
the different entries to that directory can be read using the calls to the function readdir. The
call readdir returns a directory entry in a pointer to a structure of type dirent (struct dirent*).
Such structure will contain the fields corresponding to that entry such as the name of the
entry, or the type (if it is a normal file , another directory, symbolic links, etc.). Repeated calls
to the function readdir will be returning the next entries in an open directory.<br/>
<br/>
In this lab you will be implementing three C programs which use the system calls that
were previously described. These programs will be mycat, myls and mysize. For this purpose
you will have the following files with initial code mycat.c, myls.c and mysize.c.

### mycat
The first program, mycat will open the file specified by argument and will show its
content through standard output (the console) using the calls open, read, write and close. For
this purpose:
* It will open the file specified as parameter with *open()*.
* It will read the contents of the file using an intermediate buffer of 1024 bytes
(*read()*).
* It will write (*write()*) the content of the buffer in the standard output. Use the
constant STDOUT_FILENO as value of the descriptor to write to the standard
output.
* Finally, it will close the descriptor using *close()*.
<br/>
**Usage:** `./mycat <path_input_file>`<br/>
<br/>
**Requirements**:
* The program must show the whole contents of the file.
* The program must return -1 if no argument was passed.
* The program must return -1 if there was an error when opening the file (e.g. the
file does not exist).
<br/><br/>
**Test suggestion:** Check that the output of the program over one file corresponds with the
one offered by the command cat (no extra arguments) over that same file.

### myls
The second program myls, will open a directory passed as parameter (or the current
directory if no directory is specified) and print on the screen all the entries that this directory
contains, one per line.<br/><br/>
This program will:<br/><br/>
* Obtain the specified directory from the arguments to the program or obtain the
current directory using the call *getcwd()*. Use the constant *PATH_MAX* as
maximum size that can have the path of the current directory.
* Open the directory using *opendir()*.
* Then, it will read in each of the entries of the directory using *readdir()* and print the
name of the entry using *printf()*.
* Finally, it will close the descriptor of the directory through the call *closedir()*.

**Usage:** `./myls <directory>`<br/>
**Usage 2:** `./myls`<br/>
<br/>
**Requirements:**
* The program must list all entries of the directory , in the order in which the call to
readdir returns them, and showing each entry in one line.
* The program must list the entries of the directory passed as parameter (usage 1), or
from the current directory if no parameter was passed.
* The program must return -1 if an error happened while opening the directory (e.g,
the directory does not exist)
**Test suggestion:** Check that the output of the program over a directory corresponds with the
one obtained with the command `ls -f -l` over that same directory.

### mysize
The third program, mysize, will obtain the current directory and will list all regular files
that it contains as well as its size in bytes. For this purpose:
* It will obtain the current directory using the call *getcwd()*. Use the constant
*PATH_MAX* as maximum size of the path of the current directory.
* Open the file using *opendir()*.
* Then, it will read the entries of the directory using *readir()*.
* If the entry is a regular file (field *d_type* form the structure *dirent* equal to the
constant *DT_REG*).
    * Open the file using *open()*.
    * Move the file pointer to the end of the file and obtain its value with *lseek()*.
    * Close the file with *close()*.
    * Print the name of the file (field *d_name* of the structure dirent), followed
    by a tab character, and the size obtained by *lseek()*, ending with an End
    Of Line character.
* This procedure will be repeated for every entry in the directory.
* Finally it will close the directory descriptor with *closedir()*.

**Usage:** `./mysize`<br/>
<br/>
**Requirements:**
* The program must show the name and size of all the regular files of the directory,
in the order in which the call readir returns them, and showing the data of each file
in one line.
* The program will only show the data from regular files.
* The program will show the data using the following format: `<name><tab><size>`
* The program must return -1 if there was an error when opening the file.

## Initial code

In order to facilitate the realization of this assignment an initial code is provided in the file
p1_llamadas_2017.zip. To extract its contents you can use the *unzip* command:<br/>
    `unzip p1_system_calls_2021.zip`<br/>
As a result, you will find a new directory p1_system_calls/, onto which you must code the
different programs. Inside this directory you will find:
**Makefile:**<br/>
File used by the make tool to compile all programs. Do not modify this file. Use $ make to
compile the programs and $ make clean to remove the compiled files.
**mycat.c:**<br/>
C Source file to code mycat.
**myls.c:**<br/>
C Source file to code myls
**mysize.c:**<br/>
Source file to code mysize
**p1_tests/:**<br/>
This directory contains example files and directories to be able to execute and test your
programs.

## Program tester
The python script *checker_os_p1.py* is given to verify that the student submission
follows the format conventions (it has the correct names and it is well compressed) and run
some functionality tests, printing on screen the grade obtained with the provided code. The
tester must be executed in the Linux computers of the informatic classrooms of the university:
The command to execute the tester is the following:<br/>
    `python checker_os _p1.py <submitted_file.zip>`<br/>
Being submitted_file.zip the file that it is going to be delivered in Aula Global (see next
section). Example:<br/>
    `$ /python checker_os_p1.py ssoo_p1_100254896_100047014.zip`<br/>
The Format tester will print on the console messages stating whether the required format
is correct or not.