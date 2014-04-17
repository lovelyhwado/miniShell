//
//  functions.c
//  miniShell
//
//  Created by KimGayeon on 2013. 12. 4..
//  Copyright (c) 2013년 김가연. All rights reserved.
//


#include "functions.h"

void parseInput(char input[]){
	char parse_str[BUFSIZE];
    memset(parse_str, 0, BUFSIZE);
	strcpy(parse_str,input);
    if (strcmp(parse_str, "\n")) {
        if (strstr(parse_str,";")) {
            char *toked = strtok(parse_str, ";");
            parseInput(toked);
            char tmp[BUFSIZE];
            memcpy(tmp, input, BUFSIZE);
            char *toked1 = strtok(tmp,";");
            toked1 = strtok(NULL,"\n");
            parseInput(toked1);
        } else if (strchr(parse_str,'>') || strchr(parse_str, '<') || strchr(parse_str,'|')) {
            pipeOrRedirection(input);
        } else if (strstr(parse_str, "&")) {
            char *background = strtok(parse_str, "&");
            parse(background, BACK);
            char *forground = strtok(NULL, "\n");
            if (forground != NULL) {
                parseInput(forground);
            }
        } else {
            parse(input, FOR);
        }
    }
}

void execCommand(char *argv[], int process_type){
    pid_t pid = getpid();
    int status;
    
    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    }
    
    if (pid == 0) {
        execvp(argv[0], argv);
        perror("execvp error");
        exit(1);
    }
    
    if(process_type == BACK){
        fprintf(stderr, "\n[pid : %d]\n",pid);
    } else {
        waitpid(pid, &status, 0);
    }
    return ;
}

void exeBuiltInCommand(char *argv[], int argc){
    
    if (!strcasecmp(argv[0],"cd")) {
        exeCd(argv,argc);
    } else if (!strcasecmp(argv[0], "pwd")){
        char buf[BUFSIZE];
        memset(buf, 0, BUFSIZE);
        getcwd(buf, BUFSIZE);
        printf("%s\n",buf);
    } else if (!strcasecmp(argv[0], "exit")){
        printf("exit miniShell, Bye!!\n");
        exit(0);
    } else if (!strcasecmp(argv[0], "history") || strchr(argv[0],'!')){
        historyRead(argv[0]);
    } else {
        perror("wrong command");
    }

}

void exeCd(char* argv[], int argc){
    
    if (argc >2) {
        perror("too many argments");
        return;
    } else if (argc == 1){
        if (chdir(getenv("HOME"))<0) {
            perror("change directory error");
        }
    } else{
        if (chdir(argv[1])<0) {
            perror("wrong directory");
        }
    }
}

void execs(char* argv[], int argc, int process_type){
    if (!strcasecmp(argv[0], "cd")||!strcasecmp(argv[0], "pwd")||!strcasecmp(argv[0], "exit") || !strcasecmp(argv[0], "history") || strchr(argv[0], '!')) {
        exeBuiltInCommand(argv, argc);
    } else {
        execCommand(argv, process_type);
    }
    
}

void parse(char input[], int process_type){
    int argc = 0;
    char* argv[BUFSIZE];
    memset(argv, 0, BUFSIZE);
    
    char *token = strtok(input, "\n");
    token = strtok(token, " ");
    while (token) {
        argv[argc] = token;
        token = strtok(NULL, " ");
        argc++;
    }
    
    execs(argv, argc, process_type);
}