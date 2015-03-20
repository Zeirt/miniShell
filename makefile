CFLAGS= -c -g -Wall
OFLAGS= -L./lib/Linux/i686 -lshell -o

all: execute.o  free_args.o minishell_input.o minishell.o minishell

minishell: minishell.o 
	gcc minishell.o execute.o  minishell_input.o free_args.o  $(OFLAGS) minishell

free_args.o: free_args.c
	gcc free_args.c $(CFLAGS)

minishell_input.o: minishell_input.c
	gcc minishell_input.c $(CFLAGS)

execute.o: execute.c
	gcc execute.c $(CFLAGS)

minishell.o: minishell.c 
	gcc minishell.c $(CFLAGS)

clean:
	rm *.o
	rm minishell
	echo done
