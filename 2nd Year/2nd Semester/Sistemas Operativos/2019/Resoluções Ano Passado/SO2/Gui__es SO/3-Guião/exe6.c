#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
/*
	The  system()  library  function uses fork(2) to create 
a child processt hat executes the shell command specified in 
command using execl(3).

 The return value of system() is one of the following:

       *  If command is NULL, then a nonzero value if a shell is 
available, or 0 if no shell is available.

       *  If a child process could not be created, or its status 
could not  be retrieved, the return value is -1.

       *  If  a  shell  could  not  be executed in the child process,
then the return value is as though the  child  shell  terminated  
by  calling  _exit(2) with the status 127.

       *  If  all  system calls succeed, then the return value is 
the termina‐ tion status of the child shell used to execute command.
(The termi‐  nation  status of a shell is the termination status of 
the last command it executes.)

       In the last two cases, the return value is a "wait status" 
that can  be examined  using the macros described in waitpid(2).
  (i.e., WIFEXITED(), WEXITSTATUS() and so on).


*/
int main(int argc, char *args[]){
	int status;
	pid_t pid;
	char* s; 

	if(args[0]==NULL) return 0;
	pid = fork();
	//if((perror("fork"))==NULL) return -1;

	if(pid==0){ 
		execvp(args[1], args);
		perror(args[1]);
	}else 
		wait(&status);

	if(WIFEXITED(status))
		return(WEXITSTATUS(status));

	return 1;
}