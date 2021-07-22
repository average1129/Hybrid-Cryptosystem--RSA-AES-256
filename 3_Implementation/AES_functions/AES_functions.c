#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "gmp.h" // include header 
#include <stddef.h>
#include "pkcs7_padding.h"
#include "aes.h"
#include "AES_functions.h"
#include <stdint.h>

#define CBC 1

/*typedef struct  {
uint8_t* encrypted_buffer_ptr ; // set size in define and then malloc realloc;
uint8_t encrypted_AES_KEY [16];
public_key_RSA public_key;
}Crypt;*/







void generate_key(uint8_t key_array[16])
{
memset( key_array, 0, 16 );
	
	for (int i =0; i<16; i++)
	{
		key_array[i] = (uint8_t)rand()%256;

	}

return;}

void generate_iv (uint8_t iv_array[16])
{
memset( iv_array, 0, 16 );
	
	for (int i =0; i<16; i++)
	{
		iv_array[i] = rand()%256;

	}
return;}


void initialize_AES_parameters(AES_parameters* new_parameters)
{
    
    generate_key(new_parameters->AES_KEY);
    generate_iv (new_parameters->AES_IV); 

return;
}

void print_hex_array (uint8_t * input_ptr, int buffer_size)
{
 for (uint8_t* i = input_ptr; i<input_ptr+buffer_size; i++)
    {
        printf("%u", *i);
    }
return;}



/*
uint8_t* type_convert_buffer(char buffer[], int buffer_size, uint8_t * uint8_t_buffer ) // returns address of local variable, which amed this later by passing pointer variable in arguments
{
    int padded_buffer_size = buffer_size;
    if (buffer_size%16)
    {
        padded_buffer_size+= 16 - buffer_size%16;

    } 
     
    uint8_t_buffer= (uint8_t*)calloc(padded_buffer_size,sizeof(uint8_t));
    
    for (uint8_t* i = uint8_t_buffer ; i < uint8_t_buffer+ buffer_size; i++)
    {
        *i = (uint8_t)buffer[i - uint8_t_buffer];
    } 
return uint8_t_buffer;


}
*/
