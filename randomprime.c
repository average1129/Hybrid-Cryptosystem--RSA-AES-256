#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	// first generate random odd 
	srand(time(0));
 

	 long long pos_prime= rand();
	
	 if ( pos_prime %2 == 0)
	 {
		 pos_prime ++;

	 }
	
	printf("%lld", pos_prime);
	
    return 0;
	

}