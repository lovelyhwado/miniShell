//
//  minishell.c
//  miniShell
//
//  Created by KimGayeon on 2013. 11. 30..
//  Copyright (c) 2013년 김가연. All rights reserved.
//



#include "functions.h"
#include "input.h"



int main(){
    char input_buf[BUFSIZE]; //input라인 버퍼
    
	printf("****----------------Hello, Welcome to minishell!!----------------****\n");
    
    historyInit();
    while (1) {
        memset(input_buf, 0, BUFSIZE);
        input_mode(input_buf);
        historyInsert(input_buf);
        parseInput(input_buf);
    }
    
    return 0;
    
		//if (fork() == 0) {
			//if ( redirect output ) {
			//	fd = creat(newfile, fmask);
			//	close(stdout);
			//	dup(fd);
			//	close(fd);
            // stdout is now redirected
			//}
			//	pipe(files);
			//	if ( fork() == 0 ) {
            // first component of command line
			//		close(stdout);
			//		dup(files[1]);
			//if (piping ) {
			//		close(files[1]);
			//		close(files[0]);
            // stdout now goes to pipe
            
            // child process does command1
			//		execlp(command1, command1, 0);
			//	}
            // 2nd command of command line
			//	close(stdin);
			//	dup(files[0]);
			//	close(files[0]);
			//	close(files[1]);
            // stdin now comes from pipe 
			//}
            
			//execve(command2, command2, 0);
		//}
}