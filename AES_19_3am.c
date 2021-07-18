#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "gmp.h" // include header 
#include <stddef.h>
#include "pkcs7_padding.c"
#include "aes.h"

typedef struct 
{
    uint8_t  AES_KEY[16];
    uint8_t AES_IV[16];

}AES_parameters;


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

void print_hex_array (uint8_t * input_ptr)
{
 for (uint8_t* i = input_ptr; i<input_ptr+16; i++)
    {
        printf("%u", *i);
    }
return;}

int main()
{   
    srand(time(NULL));
    AES_parameters AES_init;
    initialize_AES_parameters(&AES_init);
    

    printf("This is the randomly generated AES key:");
    print_hex_array(AES_init.AES_KEY);
    
    printf("\n");

    printf("This is the randomly generated AES IV:");
    print_hex_array(AES_init.AES_IV);
    
    printf("\n");

    return 0; 
}
