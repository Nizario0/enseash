#define _POSIX_C_SOURCE 200809L
#include "q2.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>


int q2_execute_line(const char *line, int *status) {
    if (line[0] == '\0') return 0;

    if (strcmp(line, "yoo") == 0) {
        write(STDOUT_FILENO, "salut\n", 6);
        if (status) *status = 0;
        return 0;
    }

    if (strcmp(line, "date") == 0) {
        pid_t pid = fork();
        if (pid < 0) { perror("fork"); if(status) *status = 1; return 1; }
        if (pid == 0) {
            execlp("date","date","+%Y-%m-%d %H:%M:%S.%N",NULL);
            _exit(127);
        } else {
            int wstatus;
            waitpid(pid, &wstatus, 0);
            if (status) *status = wstatus;
            return 0;
        }
    }
    
    if (strcmp(line, "crash") == 0) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); if (status) *status = 1; return 1; }
    if (pid == 0) {
        
        int *p = NULL;
        *p = 42;   // provoque SIGSEGV une shiittyy segmentation fault
        
    } else {
        int wstatus;
        waitpid(pid, &wstatus, 0);
        if (status) *status = wstatus;
        return 0;
    }
}

    
    
    if (strcmp(line, "f") == 0) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); if (status) *status = 1; return 1; }
    if (pid == 0) {
        /* enfant : se tuer immédiatement avec SIGKILL */
        kill(getpid(), SIGKILL);
        _exit(127); /* jamais atteint */
    } else {
        int wstatus;
        waitpid(pid, &wstatus, 0);
        if (status) *status = wstatus;
        return 0;
    }
}

    
    
    
    
    return 0;
}

void q2_run_repl(void) {
    char line[1024];
    int status = 0;
    while (1) {
        write(STDOUT_FILENO, "enseash % ", 10);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            write(STDOUT_FILENO, "\n", 1);
            clearerr(stdin);
            continue;
        }
        line[strcspn(line, "\n")] = '\0';
        q2_execute_line(line, &status);
    }
}

