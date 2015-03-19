CFLAGS= -c -g -Wall
OFLAGS= -L./lib/Linux/i686 -lshell -o

all: free_args.o minishell_input.o minishell.o minishell

minishell: minishell.o 
	gcc minishell.o  minishell_input.o free_args.o  $(OFLAGS) minishell

free_args.o: free_args.c
	gcc free_args.c $(CFLAGS)

minishell_input.o: minishell_input.c
	gcc minishell_input.c $(CFLAGS)

minishell.o: minishell.c 
	gcc minishell.c $(CFLAGS)

clean:
	rm *.o
	echo done
