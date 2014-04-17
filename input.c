//
//  input.c
//  miniShell
//
//  Created by KimGayeon on 2013. 12. 4..
//  Copyright (c) 2013년 김가연. All rights reserved.
//


#include "input.h"

char getch();

void shell(){
    char path[256];
    struct passwd *password;
    
    memset(path, 0, 256);
    uid_t uid = getuid();
    password = getpwuid(uid);
    getcwd(path, 256);
    
    printf("[%s : %s] $ ",password->pw_name,strrchr(path,'/')+1);
    
    
}

void move_left(){
    putc(27,stdout);
    putc(91,stdout);
    putc(68,stdout);
}

int input_mode(char *input_buf){
    int len= 0;
    char i = '\0';
    //int cursor = 0;
    //int key = 0;
    //history* history_loc = NULL;

    shell();
    while (i != '\n') {
        i = getchar();
        *(input_buf+len) = i;
        len++;
    }
   /* while (key != ENTER) {
        key = getch();
        if (key == FUNCKEY1) {
            printf("%c",key);
            key = getch();
            if (key == FUNCKEY2) {
                printf("%c",key);
                key = getch();
                if (key == UP) {
                    
                } else if (key == DOWN){
                    
                } else if (key == RIGHT){
                    if (cursor == len) {
                        putc(BEL, stdout);
                    } else {
                        printf("%c",key);
                        cursor++;
                    }
                } else if (key == LEFT){
                    if (cursor == 0) {
                        putc(BEL, stdout);
                    } else {
                        printf("%c",key);
                        cursor--;
                    }
                } else if (key == FUNCKEY3){
                    printf("%c",key);
                    key = getch();
                    if (key == DEL) {
                        if (cursor == len) {
                            putc(BEL, stdout);
                        } else {
                            for (int i = cursor; i < len; i++) {
                                input_buf[i] = input_buf[i+1];
                            }
                            input_buf[len-1] = '\0';
                            for (int i = cursor; i <len-1; i++) {
                                printf("%c",input_buf[i]);
                            }
                            printf(" ");
                            for (int i = 0; i<len-cursor; i++) {
                                move_left();
                            }
                            len--;
                        }
                    }
                }
            }
        } else if (key == BACKSPACE){
            if (cursor == 0) {
                putc(BEL, stdout);
            } else {
                
            }
        } else{
            printf("%c", key);
            input_buf[len] = (char)key;
            len++;
            cursor++;
        }
    }*/
    return 0;
}

/*char getch(){
    struct termios oldt, newt;
    int c;
    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(0, TCSANOW, &newt);
    c = getchar();
    tcsetattr(0, TCSANOW, &oldt);
    return c;
}*/