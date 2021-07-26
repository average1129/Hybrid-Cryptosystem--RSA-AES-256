#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> 
#include <string.h>
#include <stdint.h>
#include <gmp.h>
#include "aes.h"
#include "RSA.h"
#include "AES_functions.h"
#include <time.h>
#include "filefunctions.h"

#define  MAXBUFLEN 8192


/**
 * @file filefunctions.c
 * @author adityasaggar2911@gmail.com
 * @brief This file defines functions for hybrid cryptosystem and some filefunctions to handle Files directly for encryption and decryption
 * @version 0.1
 * @date 2021-07-25
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 * */

// write function to initilaize Crypt for reception
/*
initialize_Crypt_rcv (Crypt * Crypt_ptr, RSA_parameters* recieved_RSA_parameters, AES_parameters* recieved_AES_parameters, )
{
	//dependent on input socket values;
	Crypt_ptr->write_buffer = NULL;
	Crypt_ptr->padded_buffer_Size =0;
	RSA_parameters new_RSA_setup;
    //initialize_RSA(&new_RSA_setup);
	Crypt_ptr->Crypt_RSA_parameters.p = new_RSA_setup;
	//copy in values from recieved structures 


	AES_parameters new_AES_setup;
    //initialize_AES_parameters(&new_AES_setup);
	//copy in values from recieved structures

	Crypt_ptr->Crypt_AES_parameters = new_AES_setup;

	message new_message;
	initialize_message(&new_message);
	Crypt_ptr->Crypt_message = new_message;

	
}*/

/**
 * @brief This function opens a file from string with filename, and encodes it by using all parameters in initialized crypt
 *@param[in] character array that holds Filename to open 
 *@param[in] Crypt pointer to Crypt that has been initialised with all parameters 
 * @param[out] Initialized Key array
 * @return void 
 * */

//initialise Crypt before passing to read_file
void READ_FILE ( char FileName[], Crypt *Crypt_ptr) // this function will open 
{
FILE * fptr =fopen(FileName, "rw"); // take filename as user input through buffer 
if(fptr<0) {fclose(fptr), fputs("incorrect filename",stderr),exit(1);}

long fSize = FILE_SIZE(fptr);
long local_padded_buffer_size=0;
local_padded_buffer_size += 16 - fSize%16;


Crypt_ptr->write_buffer= calloc (local_padded_buffer_size, sizeof(u_int8_t)); // now write buffer is a multiple of 16 and all intiialized to 0 


if( 1!=fread(Crypt_ptr->write_buffer , fSize, 1 , fptr) )
  {fclose(fptr),free(Crypt_ptr->write_buffer),fputs("entire read fails",stderr),exit(1);}
    
//int reportPad = pkcs7_padding_pad_buffer(Crypt_ptr->write_buffer, fSize, sizeof(Crypt_ptr->write_buffer), 16 );
Crypt_ptr->padded_buffer_Size = local_padded_buffer_size; 
fclose(fptr);


}


/**
 * @brief This function opens a file from file pointer and returns the size of the file
 *@param[in] FILE pointer to File
 * @param[out] long file size
 * @return void 
 * */

long FILE_SIZE (FILE * fptr)
{
fseek (fptr, 0L, SEEK_END);
long fSize = ftell(fptr);
rewind(fptr);
return fSize;
}

/**
 * @brief This function initializes an input crypt
 *@param[in] Crypt pointer to Crypt that has not yet been initialised with all parameters 
 * @param[out] Initialized Crypt pointer
 * @return void 
 * */

void initialize_Crypt (Crypt* Crypt_ptr)
{
	
	Crypt_ptr->write_buffer = NULL;
	Crypt_ptr->padded_buffer_Size =0;
	RSA_parameters new_RSA_setup;
    initialize_RSA(&new_RSA_setup);
	Crypt_ptr->Crypt_RSA_parameters= new_RSA_setup;
	
	AES_parameters new_AES_setup;
    initialize_AES_parameters(&new_AES_setup);
	Crypt_ptr->Crypt_AES_parameters = new_AES_setup;

	message new_message;
	initialize_message(&new_message);
	Crypt_ptr->Crypt_message = new_message;

	
}

/**
 * @brief This function opens a file from string with filename, and encodes it by using all parameters in initialized crypt
  *@param[in] Crypt pointer to Crypt that has been initialised with all parameters 
 * @param[out] Encrypted Data from file has been written into write buffer
 * @param[out] File Size has been written into padded_buffer_size
 * @param[out] AES Keys are encrypted in AES KEY
 * @return void 
 * */
void encrypt_Crypt (Crypt* Crypt_ptr)
{
	struct AES_ctx encrypt_object;
	AES_CBC_encrypt_buffer(&(encrypt_object), Crypt_ptr->write_buffer, Crypt_ptr->padded_buffer_Size);
	// add set IV command 
	encrypt_AES_key(Crypt_ptr->Crypt_AES_parameters.AES_KEY,&(Crypt_ptr->Crypt_RSA_parameters), &(Crypt_ptr->Crypt_message));
	// Encrypted file contents are in the crypt->buffer, Encrypted AES keys are in Crypt->message.M
return; 
}

/*void decrypt_AES_key_HL_ (Crypt* Reciever_Crypt_ptr)
{	message  output_message;
	decrypt_AES_key(&(Reciever_Crypt_ptr->Crypt_RSA_parameters), &(Reciever_Crypt_ptr->Crypt_message), &output_message);
	char* AES_key_string= mpz_get_str(NULL,10,&(output_message.M));
	// decrypted message will now be available in output message as MPZ
	//convert mpz to string 
	

	for (int i=0; i<16; i++)
	{
		(Reciever_Crypt_ptr->Crypt_AES_parameters.AES_KEY[i])=(uint8_t)AES_key_string;
	}
	

}*/
/*

void decrypt_FILE_data (Crypt* Reciever_Crypt_ptr, message *output_message, AES_ctx* file_decryptor_object)
{	// these values will have to be stuffed into object while tranmsitting 
	//only then we can call decryption function
	decrypt_AES_key_HL(Reciever_Crypt_ptr);
	AES_init_ctx_iv(file_decryptor_object, Reciever_Crypt_ptr->Crypt_AES_parameters.AES_KEY,Reciever_Crypt_ptr->Crypt_AES_parameters.AES_IV);
	AES_CBC_decrypt_buffer(file_decryptor_object,Reciever_Crypt_ptr->write_buffer,Reciever_Crypt_ptr->padded_buffer_Size);
return;
}
*/


