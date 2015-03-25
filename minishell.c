#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>//Also included for bool variables!

#include "internals.h"
#include "execute.h"
#include "jobs.h"
#include "minishell_input.h"

int main (int argc, char *argv[])
{
	char buf[BUFSIZ];
	char s[2]=";"; //token delimiter for multiple orders
	char *token;//token storer
	bool cont=true; //keeps track of exit or not
	do
	{
		print_prompt();//print the prompt
		read_command_line(buf);//send line
		token=strtok(buf,s);//gets first token
		while(token!=NULL)//walks through the other tokens
		{
			if (strcmp(token,"exit")==0)//returns 0 if strings equal
			{
				 cont=false; //terminates
			}
			else //checks if comand is internal or external
			{
				if(is_internal_command(token))
				{
					 execute_internal_command(token);
				}
				else
				{ 
					 execute_external_command(token);
				}
			}
			token=strtok(NULL,s);//picks next token
		}
	}
	while (cont); //will exit when "false"
	
	jobs_free_mem(); //frees memory
	return 0; //ends with no errors
}
