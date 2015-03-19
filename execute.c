#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "parser.h"
#include "execute.h"
#include "free_args.h"
#include "jobs.h"


void execute_external_command(const char *command)
{
	char **args;
	int backgr=0;
	pid_t pid;
	if ((args=parser_command(command,&backgr))==NULL) 
	{
		return 1; //code 1= there is no command
	}
	
	pid=fork(); //create a child process
	
	if(pid==0)
	{
		printf("I am child: %d\n",pid);
	} else if (pid>0)
		{
			printf("I am parent: %d\n",pid);
		} 
		else
		{
			printf("Fork exploded");
			_exit(2); //exit on failure
		}
	
	parser_free_args(args);//free memory
	return 0; //all ended well
}
