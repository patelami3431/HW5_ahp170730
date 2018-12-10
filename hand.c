
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <stdlib.h>
#include <time.h>
int main (int argc,char *argv[])
{
  const gsl_rng_type * type;
  gsl_rng * random;
  gsl_rng_env_setup();
  type = gsl_rng_default;
  random = gsl_rng_alloc (type);
  if (random == NULL)
  {
  	fprintf(stderr, "\nNot enough space to allocate in the memory\n");
	exit(1);
  }
  int g =atoi(argv[2]);
  int opt;
  int u;
  int j;
  int success;
  gsl_rng_set(random,time(NULL));
while(((opt=getopt(argc,argv,"p")) != -1))
{
  switch(opt)
  {
  	case 'p':
	{
		u = gsl_rng_get(random);
  		j = abs(u%100);
  		if (j < g)
  		  success = 1;
 		else
  		  success = 2;
		break;
	}
   }
}
  gsl_rng_free (random);
  return success;
}
