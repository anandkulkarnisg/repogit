#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[])
{
	int i;
	printf ("Checking if processor is available...");
	if (system(NULL)) puts ("Ok");
	else exit (EXIT_FAILURE);
	printf ("Executing command DIR...\n");
	i=system ("dir");
	printf ("The value returned was: %d.\n",i);
	return 0;
}
