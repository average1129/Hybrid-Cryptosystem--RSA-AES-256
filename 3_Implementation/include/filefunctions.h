#ifndef _FILEFUNCTIONS_H_
#define _FILEFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<errno.h> 
#include <string.h>
#include <stdint.h>
#include "aes.h"
#include "AES_functions.h"
#include "RSA.h"
#include <time.h>



/**
 * @file filefunctions.h
 * @author adityasaggar2911@gmail.com
 * @brief This file defines the structure to hold important parameters for hybrid cryptosystem and somme filefunctions to handle Files directly for encryption and decryption
 * @version 0.1
 * @date 2021-07-25
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 * */

 /**
 * @brief Structure holds padded buffer size, the buffer where actual encryption takes place , and RSA and AES parameters structures, and a message structure holding two mpz_ts 
 * 
 * */
typedef struct {

long padded_buffer_Size;
uint8_t* write_buffer;
RSA_parameters Crypt_RSA_parameters;
AES_parameters Crypt_AES_parameters;
message Crypt_message;

}Crypt;



/**
 * @brief This function opens a file from string with filename, and encodes it by using all parameters in initialized crypt
 *@param[in] character array that holds Filename to open 
 *@param[in] Crypt pointer to Crypt that has been initialised with all parameters 
 * @param[out] Initialized Key array
 * @return void 
 * */

void READ_FILE (char FileName[], Crypt* Crypt_ptr);

/**
 * @brief This function opens a file from file pointer and returns the size of the file
 *@param[in] FILE pointer to File
 * @param[out] long file size
 * @return void 
 * */
long FILE_SIZE (FILE * fptr);
/**
 * @brief This function initializes an input crypt
 *@param[in] Crypt pointer to Crypt that has not yet been initialised with all parameters 
 * @param[out] Initialized Crypt pointer
 * @return void 
 * */
void initialize_Crypt(Crypt *Crypt_ptr);

/**
 * @brief This function opens a file from string with filename, and encodes it by using all parameters in initialized crypt
  *@param[in] Crypt pointer to Crypt that has been initialised with all parameters 
 * @param[out] Encrypted Data from file has been written into write buffer
 * @param[out] File Size has been written into padded_buffer_size
 * @param[out] AES Keys are encrypted in AES KEY
 * @return void 
 * */
void encrypt_Crypt (Crypt* Crypt_ptr);

#endif