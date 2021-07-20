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
#include "RSA.h"
#include <time.h>

typedef struct {

long padded_buffer_Size;
uint8_t* write_buffer;
uint8_t encrypted_AES_KEY[16];
uint8_t AES_IV[16];
public_key_RSA pub_key;

}Crypt;


void READ_FILE (char FileName[], Crypt* Crypt_ptr);
long FILE_SIZE (FILE * fptr);
void initialize_Crypt(Crypt *Crypt_ptr);
#endif