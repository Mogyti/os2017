#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Main before fork()\n");
	int pid = fork();
	if (pid == 0){
		printf("I'm child after fork(), lauching ps -ef\n");
		char* args[] = {"/bin/ps", "-ef", NULL};
		execvp("/bin/ps", args);
		printf("Finished lauching ps -ef\n");
	}
	else printf("I'm parent after fork(), child is %d\n", pid);

	pid = fork();
	if (pid == 0){
		printf("I'm child after fork(), lauching free -h\n");
		char* args[] = {"free", "-h", NULL};
		execvp("free", args);
		printf("Finished lauching free -h\n");
	}
	else printf("I'm parent after fork(), child is %d\n", pid);
	return 0;
}
