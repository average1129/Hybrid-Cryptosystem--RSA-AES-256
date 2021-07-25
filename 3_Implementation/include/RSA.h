#ifndef _RSA_H_
#define _RSA_H_
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h> // include header 
#include <stddef.h>


typedef struct  {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
} public_key_RSA;

typedef struct {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
    mpz_t d; /* Private Exponent */
    mpz_t p; /* Starting prime p */
    mpz_t q; /* Starting prime q */
} private_key_RSA;

typedef struct 
{
    public_key_RSA pub_k;
    private_key_RSA pri_k; 
} RSA_parameters;

typedef struct 
{
    mpz_t M;
    mpz_t C; 
    mpz_t DC;
} message; 

void block_encrypt_RSA(message* input_message, public_key_RSA* pub_k);
void block_decrypt_RSA(message* input_message,  private_key_RSA *pri_k);
void generate_AES_key(uint8_t key_array[16]);
void generate_large_prime(mpz_t* r_number);
void generate_public_key (public_key_RSA* pub_k,private_key_RSA *pri_k);
void generate_private_key (private_key_RSA *pri_k);
void initialize_message(message * new_message);
void initialize_RSA(RSA_parameters *new_parameters);
void encrypt_AES_key(int8_t aes_key[16], RSA_parameters *RSA_initialization, message *input_message);
void decrypt_AES_key(RSA_parameters *RSA_initialization, message *input_message, message*output_message);


#endif