#ifndef _RSA_H_
#define _RSA_H_
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h> // include header 
#include <stddef.h>
#include "aes.h"
#include "AES_functions.h"

/**
 * @file RSA.h
 * @author adityasaggar2911@gmail.com
 * @brief This file defines the structures to hold private and public keys for RSA. and to randomly generate key and other related functions
 * @version 0.1
 * @date 2021-07-25
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 * */

 /**
 * @brief Structure holds Modulus  and globally fixed Public Exponent both are mpz_t  
 * 
 * */
typedef struct  {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
} public_key_RSA;


 /**
 * @brief Structure holds 5 different mpz_t variables which form the private key for RSA encryption 
 * 
 * */
typedef struct {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
    mpz_t d; /* Private Exponent */
    mpz_t p; /* Starting prime p */
    mpz_t q; /* Starting prime q */
} private_key_RSA;

 /**
 * @brief Structure holds both the private and public key of an encrypted message  
 * 
 * */
typedef struct 
{
    public_key_RSA pub_k;
    private_key_RSA pri_k; 
} RSA_parameters;

 /**
 * @brief Structure holds space to encrypt and decrypt data in the form of mpz_t  
 * 
 * */
typedef struct 
{
    mpz_t M;
    mpz_t C; 
    mpz_t DC;
} message; 
/** 
 * @brief Encrypts input message based on RSA public key 
 * @param[in] message pointer to input message structure
 * @param[in] public key  pointer
 * @param[out] Encrypted message is now available in input message 
 * @return void 
 * */
void block_encrypt_RSA(message* input_message, public_key_RSA* pub_k);
/** 
 * @brief Decrypts input cipher message based on RSA private key 
 * @param[in] message pointer to input message structure 
 * @param[in] private key  pointer
 * @param[out] Decrypted message is now available in input message 
 * @return void 
 * */
void block_decrypt_RSA(message* input_message,  private_key_RSA *pri_k);
/** 
 * @brief Generates randomized AES key
 * @param[in] AES Key array 
 * @param[out] Randomized Key Array
 * @return void 
 * */
void generate_AES_key(uint8_t key_array[16]);

/** 
 * @brief generates random 1024 bit prime numbers
 * @param[in] pointer to initialized mpz_t 
 * @param[out] mpz_t set to 1024 bit prime value
 * @return void 
 * */
void generate_large_prime(mpz_t* r_number);
/** 
 * @brief Copy parameters from private key to public key 
 * @param[in] Public key pointer
 * @param[in] Private key pointer
 * @param[out] Initialized public key structure
 * @return void 
 * */
void generate_public_key (public_key_RSA* pub_k,private_key_RSA *pri_k);
/** 
 * @brief Initializes private key values and sets them
 * @param[in] pointer to private key structure
 * @param[out] Initialized private key structure
 * @return void 
 * */
void generate_private_key (private_key_RSA *pri_k);
/** 
 * @brief Initializes message structure
 * @param[in] message pointer to uninitialised message
 * @param[out] Initialized message structure
 * @return void 
 * */
void initialize_message(message * new_message);
/** 
 * @brief Initializes RSA_parameters structure
 * @param[in] RSA_p pointer to RSA_parameters structure
 * @param[out] Initialized RSA_parameters structure
 * @return void 
 * */
void initialize_RSA(RSA_parameters *new_parameters);
/** 
 * @brief Encrypts the AES key using RSA public key
 * @param[in] AES key
 * @param[in] RSA parameters structure pointer
 * @param[in] message pointer 
 * @param[out] encrypted AES key in C in message
 * @return void 
 * */
void encrypt_AES_key(int8_t aes_key[16], RSA_parameters *RSA_initialization, message *input_message);

/** 
 * @brief Decrypts the AES key using RSA private key
 * @param[in] encrypted AES key in message pointer
 * @param[in] RSA parameters structure pointer
 * @param[in] message pointer to hold decrypted AES message
 * @param[out] decrypted AES key in C in out_message
 * @return void 
 * */
void decrypt_AES_key(RSA_parameters *RSA_initialization, message *input_message, message*output_message);


#endif