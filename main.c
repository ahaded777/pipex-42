#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *cmd[] = {"/usr/bin/awk", "{print $2}", NULL};

    if (execve(cmd[0], cmd, NULL) == -1) 
    {
        perror("execve failed");
        exit(1);
    }

    return 0;
}
