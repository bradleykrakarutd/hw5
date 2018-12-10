#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>

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
	if(p < 0 || p > 100)
	{
		fprintf(stderr, "Requires p to be between 0 and 100, inclusive\n");
		return 0;
	}
	printf("%i %i %i ",p,v,trials);
	return 1;
}

