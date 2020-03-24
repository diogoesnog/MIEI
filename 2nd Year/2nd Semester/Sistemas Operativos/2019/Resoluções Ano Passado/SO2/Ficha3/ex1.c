#include <unistd.h>

/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */
/* chamadas ao sistema: defs e decls essenciais */
/*
execl(const char *path, const char *arg0, ..., NULL);
execlp(const char *file, const char *arg0, ..., NULL);
execv(const char *path, char *const argv[]);
execvp(const char *file, char *const argv[]);
*/
// 1.

int main(){
	execl("/bin/ls","ls","-l",NULL);
	return 0;
}






