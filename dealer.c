#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
	int opt;
	int i;
	int w;
	int trials;
	int scount=0;
	int status;
	pid_t mypid;
 	if (argc != 5)
	 trials = atoi(argv[3]);
	else
	 trials = atoi(argv[4]);
	char *Argv[] = {"./hand","-p", argv[2], NULL};
	while ((opt = getopt(argc,argv,"pv")) != -1)
	{
		scount = 0;
		switch(opt)
		{
			case 'v':
			{
			for (i = 0; i < trials; i++)
			{
			pid_t pid;
			if ((pid=fork()) == 0)
			{
				execv("./hand",Argv);
				exit (127);
			}
			else if (pid<0)
			{
				printf("didn't fork!");
			}
			else
			{
				//wait(NULL);
				if (waitpid(pid, &status, 0) > 0)
				{
				if (WIFEXITED(status) && WEXITSTATUS(status))
				{
				if (WEXITSTATUS(status) == 127)
				{
					printf("exec failed");
				}
				else{
					if((w=WEXITSTATUS(status)) <  atoi(argv[2]))
					{
						scount++;
						printf("\nPID  returned %d Success", w);
					}
					else
						printf("\nPID  returned %d Failure",w);
				}
				}
				}
			}
			}
			break;
			}
			case 'p':
			{
				for (i=0;i<trials;i++)
				{
					pid_t pid;
					if ((pid=fork()) == 0)
					{
						execv("./hand",Argv);
						exit(127);
					}
					else if (pid<0)
						printf("didn't fork!\n");
					else
					{
						if (waitpid(pid, &status,0)>0)
						{
						if (WIFEXITED(status) && WEXITSTATUS(status))
						{
						if (WEXITSTATUS(status) == 127)
						{
							printf("exec failed\n");
						}
						else
						{
							if ((w=WEXITSTATUS(status)) < atoi(argv[2]))
								scount++;
							else;
						}
						}
						}
					}
				}
				break;
			}
		}
	}
			float g = (scount/trials)*100;
			float f = 100 - g;
			printf ("\nCreated %d processes", trials);
			printf("\nSuccess:%.2f%% ",g);
			printf("\nFailure:%.2f%%",f);
			return 0;

}

