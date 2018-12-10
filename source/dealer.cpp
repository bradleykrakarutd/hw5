#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
using namespace std;
int main(int argc, char **argv)
{
	int x;
	int p = -1;
	bool v = false;
	int trials;
	while((x = getopt(argc, argv, "p:v::"))!= -1)
	{
		switch(x)
		{
		case 'p':
			if(optarg == NULL)
			{
				fprintf(stderr, "p requires and argument from 0 to 100.\n",optopt);
				return 0;
			}
			else
				p = atoi(optarg);
			break;
		case 'v':
			v = true;
			break;
		case '?':
			fprintf(stderr, "Invalid argument -%c \n", optopt);
		default:
			fprintf(stderr, "Invalid argument -%c \n",optopt);
			return 0;
		}
	}
	if(argv[optind] == NULL)
	{
		fprintf(stderr, "Requires number of trials\n", optopt);
		return 0;
	}
	else
		trials = atoi(argv[optind]);
	if(trials <= 0)
	{
		fprintf(stderr, "Please specify a number of trials greater than 0");
		return 0;
	}
	if(p < 0 || p > 100)
	{
		fprintf(stderr, "Requires p to be between 0 and 100, inclusive\n");
		return 0;
	}
	pid_t pid;
	int yescount = 0;
	for(int i = 0; i < trials; i++)
	{
		pid = fork();
		if(pid == -1)
			fprintf(stderr, "fork failed\n");
		else if (pid == 0)
		{
			char buffer[10];
			sprintf(buffer,"-p %i",p);
			execlp("./hand.o","./hand.o","-p 10", (char*) NULL);

			_exit(127);			
		}
		else if (pid != 0)
		{
			int status = 0;
			int cid =  wait(&status);
			int result = WEXITSTATUS(status);
			if(v == true)
			{
				printf("PID %i returned ", cid);
				if(result == 1)
					printf("success.\n");
				else
					printf("failure.\n");
			}
			if(result==1)
				yescount++;
		}
	}
	double successRate = (double)yescount/trials;
	int outRate = (int)100*successRate;
	printf("Created %i processes.\n", trials);
	printf("Success - %i%\n", outRate);
	printf("Failure - %i%\n", 100 -outRate);
	return 1;
}

