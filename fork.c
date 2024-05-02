#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    pid_t pid;
    pid = fork();

    if (pid < 0) // fork failed
    {
        fprintf(stderr, "Fork Failed");
        return;
    }
    else if (pid == 0) // child process
    {
        printf("Hello from Child\\\\n");
    }
    else // parent process
    {
        printf("Hello from Parent\\\\n");
    }
}
