//
//  redirection_pipe.c
//  miniShell
//
//  Created by KimGayeon on 2013. 12. 4..
//  Copyright (c) 2013년 김가연. All rights reserved.
//

#include "functions.h"

void piping(char *argv[], char command[]){
    int my_pipe[2];
    int status;
    pid_t pid1, pid2;
    if (pipe(my_pipe) == -1) {
        perror("pipe error");
        exit(1);
    }
    if ((pid1 = fork()) == 0) {
        if ((pid2 = fork()) == 0) {
            close(1);
            dup(my_pipe[1]);
            close(my_pipe[1]);
            close(my_pipe[0]);
            execvp(argv[0], argv);
            perror("execvp error");
            exit(1);
        }
        close(0);
        dup(my_pipe[0]);
        close(my_pipe[0]);
        close(my_pipe[1]);
        
        waitpid(pid2, &status, 0);
        if (strchr(command, '|')) {
            pipeOrRedirection(command);
        } else {
            char *argv2[BUFSIZE];
            memset(argv2, 0, BUFSIZE);
            int argc2 = 0;
            
            char *tok = strtok(command, " ");
            while (tok) {
                argv2[argc2] = tok;
                tok = strtok(NULL, " ");
                argc2++;
            }
            
            execvp(argv2[0], argv2);
            perror("execvp error");
            exit(1);
        }
    }
    
    //waitpid(pid1, &status, 0);
    
}

void redirectAppend(char command1[], char command2[]){
    int fd;
    pid_t pid;
    
    char *argv[BUFSIZE];
    memset(argv, 0, BUFSIZE);
    int argc = 0;
    
    char *tok = strtok(command1, " ");
    while (tok) {
        argv[argc] = tok;
        tok = strtok(NULL, " ");
        argc++;
    }
    command2 = strtok(command2, " ");
    if((pid =fork() )< 0){
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        if ((fd = open(command2, O_WRONLY|O_CREAT|O_APPEND, 0777))) {
            close(1);
            dup(fd);
            close(fd);
        }
        execvp(argv[0], argv);
        perror("execvp error");
        exit(1);
    }
    
}
void redirectOut(char command1[], char command2[]){
    int fd;
    pid_t pid;
    
    char *argv[BUFSIZE];
    memset(argv, 0, BUFSIZE);
    int argc = 0;
    
    char *tok = strtok(command1, " ");
    while (tok) {
        argv[argc] = tok;
        tok = strtok(NULL, " ");
        argc++;
    }
    command2 = strtok(command2, " ");
    if((pid =fork() )< 0){
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        if ((fd = open(command2, O_WRONLY|O_CREAT, 0777))) {
            close(1);
            dup(fd);
            close(fd);
        }
        execvp(argv[0], argv);
        perror("execvp error");
        exit(1);
    }
}
void redirectIn(char command1[], char command2[]){
    int fd;
    pid_t pid;
    int status;
    
    char *argv[BUFSIZE];
    memset(argv, 0, BUFSIZE);
    int argc = 0;
    
    char *tok = strtok(command1, " ");
    while (tok) {
        argv[argc] = tok;
        tok = strtok(NULL, " ");
        argc++;
    }
    command2 = strtok(command2, " ");
    if((pid =fork() )< 0){
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        if ((fd = open(command2, O_RDONLY))) {
            close(0);
            dup(fd);
            close(fd);
        }
        execvp(argv[0], argv);
        perror("execvp error");
        exit(1);
    }
    
    waitpid(pid, &status, 0);

    
}
void pipeOrRedirection(char input[]){
    char parse_str[BUFSIZE];
    memset(parse_str, 0, BUFSIZE);
    strcpy(parse_str, input);
    strtok(parse_str, "\n");
    char command1[BUFSIZE];
    memset(command1, 0, BUFSIZE);
    char command2[BUFSIZE];
    memset(command2, 0, BUFSIZE);
    if (strchr(parse_str, '|')) {
        //파이프
        int argc = 0;
        char *argv[BUFSIZE];
        memset(argv, 0, BUFSIZE);
        
        strcpy(command1, strtok(parse_str, "|"));
        strcpy(command2, strtok(NULL, "\n")+1);
        
        char *tok = strtok(command1, " ");
        while (tok) {
            argv[argc] = tok;
            tok = strtok(NULL, " ");
            argc++;
        }
        piping(argv, command2);
    } else if (strchr(parse_str, '>')){
        
        if (strstr(parse_str, ">>")) {
            // >>
            
            strcpy(command1, strtok(parse_str, ">>"));
            strcpy(command2, strtok(NULL, "\n")+1);
            
            redirectAppend(command1, command2);
        } else if(strstr(parse_str, ">!")){
            // >!
            
        } else{
            //>
            strcpy(command1, strtok(parse_str, ">"));
            strcpy(command2, strtok(NULL, "\n"));
            
            redirectOut(command1, command2);
            
        }
    } else if (strchr(parse_str, '<')){
        // <
        strcpy(command1, strtok(parse_str, "<"));
        strcpy(command2, strtok(NULL, "\n"));
        
        redirectIn(command1, command2);
        
    }
}