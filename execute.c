#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "parser.h"
#include "execute.h"
#include "free_args.h"
#include "jobs.h"

void killChild(int signal,siginfo_t *siginfo, void *context)//handler of SIGCHLD
{
	while ( (waitpid(siginfo->si_pid,0,WNOHANG))>0)//reaps zombies
	{
	}
	jobs_finished(siginfo->si_pid); //indicate the job is finished
	return;
}

void execute_external_command(const char *command)
{
	char **args;
	int backgr=0;
	int status; //keeps track of child's status
	pid_t pid; //pid of child
	struct sigaction kill;//struct for a handler

	kill.sa_sigaction=killChild;//assign SIGCHLD handler
	kill.sa_flags=SA_SIGINFO|SA_RESTART ; 
	//needs this flag to handle info + avoids running main again for no reason
	sigaction(SIGCHLD,&kill,NULL); //will go to killChild when SIGCHLD
	if ((args=parser_command(command,&backgr))==NULL) 
	{
		return; //there is no command
	}
	
	pid=fork(); //create a child process
	
	if(pid==0)//will be 0 if it's the parent
	{
		if(execvp(*args,args)<0)//executes order, returns negative if fail
		{
			printf("The execution has failed! \n");
			exit(1); //exit on failure
		}
		//pid=getpid(); //might be useless, keep in mind
	 }
	else if (pid>0) //won't be 0 if it's the child
		{
			jobs_new(pid,args[0]);//registers child as job
			if(backgr==0) //no bg, if bg, parent doesn't wait
			{
				wait(&status); //parent waits for child to finish
			}
			else
			{
				waitpid(pid,&status,WNOHANG); //parent doesn't block
			}

		}
		else//if pid <0, fork has failed
		{
			printf("Fork has failed!");
		}
	
	parser_free_args(args);//free memory
	return; //go back, main() starts over
}
