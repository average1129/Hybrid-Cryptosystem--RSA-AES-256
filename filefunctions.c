#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<errno.h> 
#include <string.h>
#include <stdint.h>
#include "aes.h"
#include "AES_functions.h"
#include <time.h>
#include "filefunctions.h"

#define  MAXBUFLEN 8192


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
    
int reportPad = pkcs7_padding_pad_buffer(Crypt_ptr->write_buffer, fSize, sizeof(Crypt_ptr->write_buffer), 16 );
Crypt_ptr->padded_buffer_Size = local_padded_buffer_size; 
fclose(fptr);


}


long FILE_SIZE (FILE * fptr)
{
fseek (fptr, 0L, SEEK_END);
long fSize = ftell(fptr);
rewind(fptr);
return fSize;
}


void intialize_Crypt (Crypt* Crypt_ptr)
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

void encrypt_Crypt (Crypt* Crypt_ptr)
{
	struct AES_ctx encrypt_object;
	AES_CBC_encrypt_buffer(&(encrypt_object), Crypt_ptr->write_buffer, Crypt_ptr->padded_buffer_Size);
	
} 


