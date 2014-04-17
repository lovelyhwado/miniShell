//
//  functions.h
//  miniShell
//
//  Created by KimGayeon on 2013. 12. 4..
//  Copyright (c) 2013년 김가연. All rights reserved.
//

#ifndef minishell_function_h
#define minishell_function_h

#include "headers.h"
#define BUFSIZE 256

#define FOR     0
#define BACK    1
#define REDORPIPE 2
#define PIPE 3


void parseInput(char input_buf[]);
void exeCd(char* argv[], int argc);
void parse(char input[], int process_type);
void execs(char* argv[], int argc, int process_type);

void pipeOrRedirection(char *input);
int redirection(char* process_buf,int process_type);

void historyInit();
void historyInsert(char input_buf[]);
void historyRead(char input_buf[]);

#endif