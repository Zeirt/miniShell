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
		return;
	}

	//code here

	return;
}
