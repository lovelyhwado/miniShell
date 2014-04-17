//
//  history.c
//  miniShell
//
//  Created by KimGayeon on 2013. 12. 4..
//  Copyright (c) 2013년 김가연. All rights reserved.
//

#include "functions.h"

int history_fd;

void historyInit(){
    
    if ((history_fd = open(".history",O_RDWR|O_CREAT|O_TRUNC,0777))<0) {
        perror("open failed");
        exit(1);
    }
}

void historyInsert(char input_buf[]){
    size_t input_size = strlen(input_buf);
    write(history_fd, input_buf, input_size);
}

void historyRead(char input_buf[]){
    char *read_buf = (char*) malloc(1024);
    char *history_list[BUFSIZE];
    memset(history_list, 0, BUFSIZE);
    ssize_t readsize;
    int count = 0;
    int fd;
    if ((fd= open(".history", O_RDONLY))>0) {
        int i = 0;
        while ((readsize = read(fd, read_buf+i, 1)) >0)  {
            i += (int)readsize;
        }
        char *tok = strtok(read_buf, "\n");
        while (tok) {
            history_list[count] = tok;
            tok = strtok(NULL, "\n");
            count++;
        }
    } else{
        perror("open failed");
        exit(1);
    }
    
    close(fd);
    
    if (!strcmp(input_buf, "history")) {
        for (int i = 0; i<count; i++) {
            printf("%d %s\n",i+1,history_list[i]);
        }
    } else if (!strcmp(input_buf, "!!")) {
        parseInput(history_list[count-2]);
    } else {
        int line_number;
        char tmp[BUFSIZE];
        memset(tmp, 0, BUFSIZE);
        strcpy(tmp, (input_buf+1));
        line_number = atoi(tmp);
        
        if (line_number > 0 && line_number <= count) {
            parseInput(history_list[line_number-1]);
        } else {
            perror("not right number");
            exit(1);
        }
    }
}