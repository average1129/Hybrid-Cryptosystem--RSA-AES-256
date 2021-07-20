#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "gmp.h" // include header 
#include <stddef.h>
#include "RSA.h"

void block_encrypt_RSA(message* input_message, public_key_RSA* pub_k)// before inputtinh to function typecast C & M to mpz_t 
{
    /* C = M^e mod n */
    mpz_powm(input_message->C, input_message->M, pub_k->e, pub_k->n); 
    return;
}

void block_decrypt_RSA(message* input_message,  private_key_RSA *pri_k)
{
    mpz_powm(input_message->M, input_message->C, pri_k->d, pri_k->n); 
    return;
}

void generate_AES_key(uint8_t key_array[16]) //sequence to be encrypted in this test
{
memset( key_array, 0, 16 );
	
	for (int i =0; i<16; i++)
	{
		key_array[i] = (uint8_t)rand()%256;

	}

}

void generate_large_prime(mpz_t* r_number)
{
    int rndBit=1023; 					// bound for mpz_randb
	
	gmp_randstate_t random_state; // random generator state object    	
	 
	gmp_randinit_default(random_state); // initilize random state with default algorithm 	
		
	//defining seed with unsigned long before beginning 
	unsigned long seed = (unsigned long)(time(NULL));	
	
	gmp_randseed_ui(random_state, seed);

	   
    mpz_urandomb(*r_number, random_state, rndBit);
    	
	int odd_check = mpz_odd_p (*r_number); 		// returns non zero if odd 
	if (odd_check==0) 							// if result is zero, that is term is even -> enter if condition 
	{
		unsigned long int one =1;
		mpz_add_ui ( *r_number, *r_number, one);  // now r_number is odd 
	}
	
	int reps= 40 ; // number of times to run primality test;
	mpz_t prime_1024;
	mpz_init (prime_1024);
	
	int primality_test = mpz_probab_prime_p (*r_number,  reps); //Return 2 if n is definitely prime, 	
													//return 1 if n is probably prime (without being certain), or return 0 if n is definitely non-prime.
		
	if(primality_test!=2)
	{
		mpz_nextprime (*r_number, *r_number);	
		//primality_test =  mpz_probab_prime_p (r_number,  reps);
	}	
	mpz_t tmp; mpz_init(tmp);
    mpz_t local_e; mpz_init(local_e); mpz_set_ui(local_e, 65537);

	mpz_mod(tmp, *r_number, local_e);        /* If p mod e == 1, gcd(phi, e) != 1 */
    while(!mpz_cmp_ui(tmp, 1))         
    {
        mpz_nextprime(*r_number, *r_number);    /* so choose the next prime */
        mpz_mod(tmp, *r_number, local_e);
    }
	

}

void generate_public_key (public_key_RSA* pub_k,private_key_RSA *pri_k)
{

mpz_set(pub_k->n, pri_k->n);
return;
} 

void generate_private_key (private_key_RSA *pri_k)
{   
    mpz_t phi; mpz_init(phi);
    mpz_t tmp1; mpz_init(tmp1);
    mpz_t tmp2; mpz_init(tmp2);
 
    mpz_t * prime_p_ptr = &(pri_k->p);
    mpz_t * prime_q_ptr= &(pri_k->q);

    generate_large_prime (prime_p_ptr);
    generate_large_prime (prime_q_ptr);
    
    while (mpz_cmp(*prime_p_ptr, *prime_q_ptr) == 0){
        generate_large_prime (prime_q_ptr);
    }    

    mpz_mul(pri_k->n, pri_k->p, pri_k->q);

	mpz_sub_ui(tmp1, pri_k->p, 1);
    mpz_sub_ui(tmp2, pri_k->q, 1);
    mpz_mul(phi, tmp1, tmp2);

	if(mpz_invert(pri_k->d, pri_k->e, phi) == 0)
	{
		printf("Invert Failed");
	}
return;
}
void initialize_message(message * new_message)
{
    mpz_init(new_message->C);
    mpz_init(new_message->M);
    mpz_init(new_message->DC);
}

void initialize_RSA(RSA_parameters *new_parameters)
{
    
    mpz_init(new_parameters->pri_k.p);
    mpz_init(new_parameters->pri_k.q);
    mpz_init(new_parameters->pri_k.n);
    mpz_init(new_parameters->pri_k.e);
    mpz_init(new_parameters->pri_k.d);
    mpz_set_ui(new_parameters->pri_k.e, 65537 );

    mpz_init(new_parameters->pub_k.n);
    mpz_init(new_parameters->pub_k.e);
    mpz_set_ui(new_parameters->pub_k.e, 65537 );

    


    generate_private_key (&(new_parameters->pri_k));
    generate_public_key (&(new_parameters->pub_k),&(new_parameters->pri_k));
    
    
	return;


}

void encrypt_AES_key(int8_t aes_key[16], RSA_parameters *RSA_initialization, message *input_message)
{
    int size_AES_key = 16*sizeof(uint8_t);
    mpz_import(input_message->M, size_AES_key, 1, sizeof(aes_key[0]), 0, 0, aes_key);   
    block_encrypt_RSA(input_message,&(RSA_initialization->pub_k));
    return; 
}


void decrypt_AES_key(RSA_parameters *RSA_initialization, message *input_message, message*output_message)
{
    *(output_message->C) = *(input_message->C);
    block_decrypt_RSA(output_message,&(RSA_initialization->pri_k));
    
    
    return; 
}

int main()
{   srand(time(NULL));
    uint8_t AES_key[16];
    generate_AES_key(AES_key);
    
    printf("This is the randomly generated AES key:");
    for (int i =0; i<16; i++)
    {
        printf("%u", AES_key[i] );
    }
    printf("\n");

    RSA_parameters new_RSA_setup;
    initialize_RSA(&new_RSA_setup);
    
    message secret;
    message secret_revealed;
    initialize_message(&secret);
    initialize_message(&secret_revealed);
    encrypt_AES_key(AES_key, &new_RSA_setup,&secret);

     char* tmp5 = mpz_get_str(NULL,10,secret.M);
    printf ("This is the AES key passed to be encrypted: %s \n", tmp5);

    char* tmp6 = mpz_get_str(NULL,10,secret.C);
    printf ("This is encrypted AES key: %s \n", tmp6);

    

    char* tmp = mpz_get_str(NULL,10,new_RSA_setup.pri_k.d);
    printf ("This is d : %s \n", tmp);

     char* tmp1 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.p);
    printf ("This is p : %s \n", tmp1);

   char* tmp2 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.q);
    printf ("This is q : %s \n", tmp2);

    char* tmp3 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.n);
    printf ("This is n : %s \n", tmp3);
    
    char* tmp4 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.e);
    printf ("This is e: %s \n", tmp4);
    

    decrypt_AES_key(&new_RSA_setup,&secret,&secret_revealed);
    char* tmp9 = mpz_get_str(NULL,10,secret_revealed.M);
    printf ("This is the decrypted AES key: %s \n", tmp9);

    
    return 0; 
}
