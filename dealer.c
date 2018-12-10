#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
	if( (argc != 4) && (argc != 5))
		fprintf(stderr, "Not enough arguments!");
	int opt;
	int i;
	int w;
	int trials;
	int scount=0;
	int status;
	pid_t mypid;
	int p = atoi(argv[2]);
 	if (argc != 5)
	 trials = atoi(argv[3]);
	else
	 trials = atoi(argv[4]);
	if(!((p>=0) && (p<=100)))
	{
		fprintf(stderr,"Invalid Percentage!");
		exit(1);
	}

	char *Argv[] = {"./hand","-p", argv[2], NULL};
	while ((opt = getopt(argc,argv,"p:v:")) != -1)
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
				fprintf(stderr,"didn't fork!");
				exit(1);
			}
			
			//sleeping for 2 secs so child terminates

				sleep(1);
				if (waitpid(pid, &status, 0) > 0)
				{
				if (WIFEXITED(status) && WEXITSTATUS(status))
				{
				if (WEXITSTATUS(status) == 127)
				{
					fprintf(stderr,"exec failed");
					exit(1);
				}
				else{
					if((w=WEXITSTATUS(status)) !=  atoi("2"))
					{
						scount++;
						printf("\nPID %d returned Success", pid);
					}
					else
						printf("\nPID %d returned Failure",pid);
				}
				}
				}
			}
			break;
			}
			case 'p':
			{
				if (argc != 5)
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
					{
						printf("didn't fork!\n");
						exit(1);
					}
					sleep(1);
						if (waitpid(pid, &status,0)>0)
						{
						if (WIFEXITED(status) && WEXITSTATUS(status))
						{
						wait(&status);
						if (WEXITSTATUS(status) == 127)
						{
							printf("exec failed\n");
							exit(1);
						}
						else
						{
							if ((w=WEXITSTATUS(status)) !=  atoi("2"))
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
			float g = ((float)scount/trials)*100.0;
			float f = 100.0 - g;
			printf ("\nCreated %d processes", trials);
			printf("\nSuccess:%.2f%% ",g);
			printf("\nFailure:%.2f%%\n",f);
			return 0;

}

