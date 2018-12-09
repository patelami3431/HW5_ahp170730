#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
	int opt;
	int i;
	int trials;
	int scount=0;
	int status;
	pid_t pid;
	pid_t mypid;
 	if (argc != 5)
	 trials = atoi(argv[3]);
	else
	 trials = atoi(argv[4]);
	char *Argv[] = {"./a.out","-p", argv[2], NULL};
//	while ((opt = getopt(argc,argv,"pv")) != -1)
//	{
//		switch(opt)
//		{
//			case 'p':
//			{
			for (i = 0; i < trials; i++)
			{
			 if ((pid=fork()) == 0)
			 //in child
			 {
				execv("./a.out",Argv);
				exit (3);
			}
			else
			{
				//pid_t childpid = wait
				if (waitpid(pid, &status, 0) > 0)
				{
				if (WIFEXITED(status) && WEXITSTATUS(status))
				{
				if (WEXITSTATUS(status) == 3)
				{
					//exec failed
				}
				else{
					if(WEXITSTATUS(status) >  atoi("0"))
					{
						scount++;
						printf("\nPID %d returned Success",pid );
					}
					else
						printf("\nPID %d returned Failure",pid);
				}
				}
				}
				wait(&status);
			}
			}
			float g = (scount/trials)*100;
			float f = 100 - g;
			printf ("\nCreated %d processes", trials);
			printf("\nSuccess:%.2f%% ",g);
			printf("\nFailure:%.2f%%",f);
			return 0;

}

