#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main() {
	 // create 1024 bit prime number 
	//mpz_t int_1024 ;
	//mpz_init(int_1024);
	
	// generation of random number is attempted 
	mpz_t r_number; 				// holds random number 
	int rndBit; 					// bound for mpz_randb
	mpz_init(r_number); 	        // initializing rnum before use 
	mpz_t number_2;
	mpz_init (number_2);
	mpz_init_set_str(number_2, "2", 10);
	gmp_randstate_t random_state;	// random generator state object    	
	rndBit = 1023;
	
	// initilize random state with default algorithm 	
	gmp_randinit_default(random_state);
	
	
	//defining seed with unsigned long before beginning 
	unsigned long seed = (unsigned long)(time(NULL));
	

	gmp_randseed_ui(random_state, seed);
	printf("1 random numbers in U[0, -1+2**%d]:\n", rndBit);
	
	
    /* mpz_get_ui() can convert r_number to unsigned long int... */
    mpz_urandomb(r_number, random_state, rndBit);
    mpz_out_str(stdout, 1, r_number);
	printf("\n");
	
	
	for (int i =0; i<1023;i++)
	{
		
	}
	//gmp_randclass::get_z_bits () 
		
	//gmp_randinit_mt (random_state);
	
    //mpz_urandomb(r_number, state, size)
    
	/* Clean up resources occupied by compensated */
  gmp_randclear(random_state);

  /* Clean up resources occupied by our mpz_t variables */
  mpz_clear(r_number);
	return 0;
}

