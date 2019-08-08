// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "TutorialConfig.h"

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout,"%s Version %d.%d\n",
				argv[0],
				Tutorial_VERSION_MAJOR,
				Tutorial_VERSION_MINOR);
		fprintf(stdout,"Usage: %s number\n",argv[0]);
		return 1;
	}
	double inputValue = atof(argv[1]);
#if defined (HAVE_LOG) && defined(HAVE_EXP)
	std::cout << "have exp and log" << std::endl;
	double outputValue = exp(log(inputValue) * 0.5);
#else
	std::cout << "no exp or no log" << std::endl;
	double outputValue = sqrt(inputValue);
#endif
	fprintf(stdout,"The square root of %g is %g\n",
			inputValue, outputValue);

#if defined (HAVE_MYFUNC)
	std::cout << "have myfunc" << std::endl;
#else
	std::cout << "have not myfunc" << std::endl;
#endif

	return 0;
}
