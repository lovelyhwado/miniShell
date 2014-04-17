CC = gcc
CFLAGS = -Wall -g
OBJECTS = minishell.o functions.o input.o redirection_pipe.o history.o
EXEC = minishell

.c.o: functions.h headers.h input.h
	$(CC) $(CFLAGS) -c $<

minishell: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o $(EXEC)
