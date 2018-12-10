#include <stdio.h>
#include <unistd.h>
#include <gsl/gsl_rng.h>
#include <stdlib.h>
#include <ctime>
#include <sys/types.h>
using namespace std;
gsl_rng_type *_gsl_rng_type;
gsl_rng * _gsl_rng;
int main(int argc, char** argv)
{
	getopt(argc, argv, "p:");
	int p = atoi(optarg);
	_gsl_rng = gsl_rng_alloc(gsl_rng_mt19937);
	time_t result = time(NULL);
	result += getpid();
	gsl_rng_set(_gsl_rng,result); 
	double rand = gsl_rng_uniform(_gsl_rng) * 100.0;
	gsl_rng_free(_gsl_rng);
	if(rand < (double)p)
		return 1;
	else
		return 0;
}
	
