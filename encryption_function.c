#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gmp.h>
#include <time.h>
#include <pthread.h>


#define E 65537

/*
typedef struct public_key
{
	E;
	mpz_t n;
	
}public_key;
*/

void prime_generator (mpz_t r_number)
{// generation of random number is attempted 
					 
	int rndBit=1023; 					// bound for mpz_randb
	
	gmp_randstate_t random_state; // random generator state object    	
	 
	gmp_randinit_default(random_state); // initilize random state with default algorithm 	
		
	//defining seed with unsigned long before beginning 
	unsigned long seed = (unsigned long)(time(NULL));	
	
	gmp_randseed_ui(random_state, seed);

	   
    mpz_urandomb(r_number, random_state, rndBit);
    	
	int odd_check = mpz_odd_p (r_number); 		// returns non zero if odd 
	if (odd_check==0) 							// if result is zero, that is term is even -> enter if condition 
	{
		unsigned long int one =1;
		mpz_add_ui ( r_number, r_number, one);  // now r_number is odd 
	}
	
	int reps= 40 ; // number of times to run primality test;
	mpz_t prime_1024;
	mpz_init (prime_1024);
	
	int primality_test = mpz_probab_prime_p (r_number,  reps); //Return 2 if n is definitely prime, 	
													//return 1 if n is probably prime (without being certain), or return 0 if n is definitely non-prime.
		
	if(primality_test!=2)
	{
		mpz_nextprime (r_number, r_number);	
		//primality_test =  mpz_probab_prime_p (r_number,  reps);
	}	
	
	
	mpz_set (prime_1024, r_number);
	

  gmp_randclear(random_state);
}

void* prime_generator_worker (void* arg)
{	mpz_t r_number;
	mpz_init (r_number);
	
 	mpz_t* prime_number_out = (mpz_t*) calloc (1, sizeof(mpz_t));
 	
 	prime_generator(r_number);
	//mpz_out_str(stdout, 1, r_number);
	//printf("\n");
	mpz_set (*prime_number_out, r_number);
 	// now i can free r_number
 	mpz_clear(r_number);
 
 pthread_exit (prime_number_out);
}

*mpz_t create_p_q()
{
pthread_t prime_threads_p;
pthread_t prime_threads_q;
pthread_create(&prime_threads_p,NULL, prime_generator_worker, NULL);

sleep(1); // move to usleep or nanosleep 

pthread_create(&prime_threads_q, NULL, prime_generator_worker,NULL);


mpz_t * prime_1024[2] ; // prime_1024[0] = p 
						// prime_1024[1] =q

pthread_join (prime_threads_p, (void**)&prime_1024[0]); 
pthread_join (prime_threads_q, (void**)&prime_1024[1]);
	
printf("The value of p is: \n");	
mpz_out_str(stdout, 1, *prime_1024[0]);
printf("\n\n");
printf("The value of q is: \n");
mpz_out_str(stdout, 1, *prime_1024[1]);

return prime_1024;
}

mpz_t* phi(mpz_t * input_p_q_array )
{	mpz_t * phi_p;
 
	mpz_t p_minus1, q_minus1;
	mpz_inits(p_minus1,q_minus1);
	mpz_set (p_minus1, *input_p_q_array);
	mpz_set (p_minus1, *(input_p_q_array+1));
	unsigned long int one= 1;
	mpz_sub_ui (p_minus1, p_minus1, one);
	mpz_sub_ui (q_minus1, q_minus1, one); // now we have p-1 and q-1 
	mpz_mul (*phi_p, p_minus1 op1, q_minus1);
	
 return phi_p;
}

mpz_t* calculate_privatekey (const mpz_t * phi_p) // do i really need to use pointers for this?
{
		
int invert_return_value;
mpz_t private_key;
mpz_init(private_key);
invert_return_value=mpz_invert (mpz_t rop, E, *phi_p); //the value of private key will be returned in rop
	
	/*if (invert_return_value==0)
	{
		//error; 
		write code to throw error
	}*/
}

int main ()
{	
	

	
return 0;
}