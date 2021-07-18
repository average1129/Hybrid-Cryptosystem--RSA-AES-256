#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "gmp.h" // include header 
#include <stddef.h>
#include "pkcs7_padding.c"
#include "aes.h"

#define CBC 1


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

void print_hex_array (uint8_t * input_ptr, int buffer_size)
{
 for (uint8_t* i = input_ptr; i<input_ptr+buffer_size; i++)
    {
        printf("%u", *i);
    }
return;}

void type_convert_buffer(char buffer[], int buffer_size, uint8_t output_buffer[])
{
    int padded_buffer_size = buffer_size;
    if (buffer_size%16)
    {
        padded_buffer_size+= 16 - buffer_size%16;

    } 
     
    
    memset (output_buffer,0, padded_buffer_size);
    for (int i =0 ; i <buffer_size; i++)
    {
        output_buffer[i] = (uint8_t)buffer[i];
    } 

return;

}

int main()
{   
    srand(time(NULL));
    AES_parameters AES_init;
    initialize_AES_parameters(&AES_init);
    

    printf("This is the randomly generated AES key:");
    print_hex_array(AES_init.AES_KEY,16);
    
    printf("\n");

    printf("This is the randomly generated AES IV:");
    print_hex_array(AES_init.AES_IV,16);
    
    printf("\n");

    struct AES_ctx encrypt_object;


    AES_init_ctx_iv(&(encrypt_object), AES_init.AES_KEY, AES_init.AES_IV);
    
    char buffer[1000];
    printf("Enter input to be encrypted:\n");
    scanf("%s",buffer);


    uint8_t * uint8_t_buffer ;
    type_convert_buffer(buffer,strlen(buffer), uint8_t_buffer);
    int string_lenght = strlen(buffer); // this is just for testing to see uint8_t version of input 
    
    printf("\nthis is the input buffer in hex: ");
    void print_hex_array(u_int8_t_buffer,string_lenght);

    int padded_buffer_size;
    padded_buffer_size += 16 - strlen(buffer)%16;
    AES_CBC_encrypt(&(encrypt_object), uint8_t_buffer, padded_buffer_size);
    

    printf("\nThis is the encrypted buffer\n");
    void print_hex_array(u_int8_t_buffer, padded_buffer_size);


    AES_CBC_decrypt(&(encrypt_object), uint8_t_buffer,padded_buffer_size);

    printf("\nThis is the decrypted buffer\n");
    void print_hex_array (uint8_t *u_int8_t_buffer, int padded_buffer_size);


    return 0; 
}