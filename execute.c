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
	int status; //keeps track of child's status
	pid_t pid,ppid; //pid of child and parent
	if ((args=parser_command(command,&backgr))==NULL) 
	{
		return; //there is no command
	}
	
	pid=fork(); //create a child process
	
	/*if(pid==0)
	{
		printf("I am child: %d\n",pid);
	} else if (pid>0)
		{
			printf("I am parent: %d\n",pid);
		} 
		else
		{
			printf("Fork exploded");
			_exit(1); //exit on failure
		}*/

	if(pid==0)//will be 0 if it's the parent
	{
		ppid=getpid(); //get the pid of parent
		if(execvp(*args,args)<0)//executes order, returns negative if fail
		{
			printf("The execution has failed! \n");
			exit(1); //exit on failure
		}
	 }
	else if (pid>0) //won't be 0 if it's the child
		{
			//jobs_new(pid,'c');//add name stuff later, registers child
			ppid=wait(&status); //parent waits for child to finish
		}
	
	jobs_finished(pid); //indicates the job/process is done
	
	parser_free_args(args);//free memory
	return; //go back, main() starts over
}
