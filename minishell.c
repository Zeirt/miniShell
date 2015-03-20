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
	
	bool cont=true; //keeps track of exit or not
	do
	{
		print_prompt();//print the prompt
		read_command_line(buf);//send line
		if (strcmp(buf,"exit")==0)//returns 0 if strings equal
		{
			 cont=false; //terminates
		}
		else //checks if comand is internal or external
		{
			if(is_internal_command(buf))
			{
				 execute_internal_command(buf);
			}
			else
			{ 
				 execute_external_command(buf);
			}
		}
	}
	while (cont); //will exit when "false"
	
	jobs_free_mem(); //frees memory
	return 0; //ends with no errors
}
