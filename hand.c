
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <stdlib.h>

int main (int argc,char *argv[])
{
  const gsl_rng_type * type;
  gsl_rng * random;
  gsl_rng_env_setup();
  type = gsl_rng_default;
  random = gsl_rng_alloc (type);
  int g =atoi(argv[2]);
  int opt;
  int u;
  int j;
  int success;
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
  		  success = 0;
		break;
	}
   }
}
  gsl_rng_free (random);
  return success;
}