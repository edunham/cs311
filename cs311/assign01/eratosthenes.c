/*
 * Author: Emily Dunham
 * Date: 10/1/2012
 * Resources and credits and such: I had to Google an embarrassingly large
 * number of basic C programming things that I'd forgotten since 261, but
 * did not view any other students' code, nor did I show my code to anyone.
 * */



#include <stdio.h>
#include <math.h>
#include <limits.h>
#define MARK 1
#define UNMARKED 0

void sieve(int n, int* primes, int* ptr)
{
	/*
 	* Calling function ought to malloc the array in which primes end up
 	* and also the pointer to its top (primitive stack implementation)
 	* so that it can get the primes out easier. 
 	*
 	* Note the naive lack of error checking for correct setup.
 	*
 	* The array primes contains all prime numbers found, and ptr
 	* has the number of primes found. 
  	*/
	int stop;
	stop = sqrt(n);
	int k=1;
 	int m = k;
	int counter = 0;
	char* array = (char*)calloc(n, sizeof(char));
	array[0] = MARK;
	array[1] = MARK;
	while (k <= stop)
	{
		do{
			m++;
		} while (array[m] == MARK);
		counter = 2; 
		while(counter*m <= n)
		{
			array[counter*m] = MARK;
			counter++;
		}
		k = m;
	}
	int i=0;
	while (i<n)
	{
		if(array[i]==UNMARKED)
		{
			primes[*ptr] = i+1;
			*ptr=(*ptr)+1;
		}
		i++;
	}	

}
void printarray(int* arr, int max)
{
	printf("Found %d primes:\n", max);
	int i=0;
	int cols = 5;
	while(i < max){
		printf("%d", arr[i]-1);
		if (i%cols==0)
			printf("\n");
		else
			printf("\t");
		i++;

	}
	printf("\n");
}
int main(int args, char *argc)
{
	int n;
	/* Interact */
	printf("Welcome to the Sieve of Eratosthenes!\n");
	printf("Enter the number, n, up to which we shall find primes: ");
	scanf("%d", &n);
	if ((n<=1)||(n>=INT_MAX))
	{
		printf("Illegal value for n. Aborting...");
		return 0;
	}
	/* Setup */
	int* primes;
	primes = (int*)malloc((n/2)*sizeof(int));
	int ptr = 0;
	int i=0;
	/* Sift & Print */
	sieve(n, primes, &ptr);
	printarray(primes, ptr);
	return 0;
}

