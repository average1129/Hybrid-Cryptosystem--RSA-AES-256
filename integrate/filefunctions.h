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

typedef struct {

long padded_buffer_Size;
uint8_t* write_buffer;
RSA_parameters Crypt_RSA_parameters;
AES_parameters Crypt_AES_parameters;
message Crypt_message;

}Crypt;


void READ_FILE (char FileName[], Crypt* Crypt_ptr);
long FILE_SIZE (FILE * fptr);
void initialize_Crypt(Crypt *Crypt_ptr);
void encrypt_Crypt (Crypt* Crypt_ptr);

#endif