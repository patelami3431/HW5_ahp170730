#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<ctype.h>
int main(int argc, char *argv[])
{
	if((argc < 4) || (argc > 5))
	{
		fprintf(stderr, "Not enough arguments! Try again..\n");
		fprintf(stderr,"ERROR 401: Arguments not of the form: ./dealer [-p] [value] [-v|NULL] [int value]\n");
		exit(1);
	}
		
	int opt;
	int i;
	int w;
	int p = atoi(argv[2]);
	int trials;
	int scount=0;
	int status;
	int pThere=0;
	pid_t mypid;
	if (argc != 5)
	 trials  = atoi(argv[3]);
	else
	 trials = atoi(argv[4]);

	if(!((p>=0) && (p<=100)))
	{
		fprintf(stderr,"Invalid Percentage! Try again..");
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
			if(pThere)
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
				fprintf(stderr,"Oops, didn't fork! Try again..");
				exit(1);
			}
			
			//sleeping for 1 secs so child terminates

				sleep(1);
				if (waitpid(pid, &status, 0) > 0)
				{
				if (WIFEXITED(status) && WEXITSTATUS(status))
				{
				if (WEXITSTATUS(status) == 127)
				{
					fprintf(stderr,"Oops, exec failed! Try again..(Check the env variables!)");
					exit(1);
				}
				else{
					if((w=WEXITSTATUS(status)) !=  atoi("2"))
					{
						scount++;
						printf("PID %d returned Success.\n", pid);
					}
					else
						printf("PID %d returned Failure.\n",pid);
				}
				}
				}
			}
			}
			else
			{
				fprintf(stderr, "ERROR 401: Arguments not of the form: ./dealer [-p] [value] [-v|NULL] [int value]]\n");
				exit(1);
			}
			break;
			}
			case 'p':
			{
				pThere = 1;
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
						printf("Oops, didn't fork! Try again..\n");
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
							printf("Oops, exec failed! Try again.. (Check the env variables!)\n");
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
			default:
				fprintf(stderr, "ERROR 401: Arguments not of the form: ./dealer [-p] [value] [-v|NULL] [int value]]\n");
				exit(1);
		}
	}
			float g = ((float)scount/trials)*100.0;
			float f = 100.0 - g;
			printf ("Created %d processes.\n", trials);
			printf("Success:%.2f%%\n",g);
			printf("Failure:%.2f%%\n",f);
			return 0;

}

