#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
//#include "gmp.h" // include header 
#include <stddef.h>
#include "../include/pkcs7_padding.h"
#include "../lib/aes.h"
#include "../include/AES_functions.h"

#define CBC 1





/*typedef struct  {
uint8_t* encrypted_buffer_ptr ; // set size in define and then malloc realloc;
uint8_t encrypted_AES_KEY [16];
public_key_RSA public_key;
}Crypt;*/


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
    (void)scanf("%s",buffer);
    int buffer_size = strlen(buffer) ;
    int padded_buffer_size=0;
    padded_buffer_size += 16 - buffer_size%16;
    
    
    /*
    uint8_t * uint8_t_buffer = NULL;
    type_convert_buffer(buffer, buffer_size, uint8_t_buffer);
    */
    uint8_t uint8_t_buffer[padded_buffer_size];
    memset( uint8_t_buffer, 0, padded_buffer_size );

    for (int i=0;i<buffer_size;i++) {
        uint8_t_buffer[i] = (uint8_t)buffer[i];
    }

    
    
   // int reportPad = pkcs7_padding_pad_buffer( uint8_t_buffer, buffer_size, sizeof(uint8_t_buffer), 16 );

     printf("The padded input STRING in hex is = ");
     print_hex_array(uint8_t_buffer, padded_buffer_size); printf("\n");

    AES_CBC_encrypt_buffer(&(encrypt_object), uint8_t_buffer, padded_buffer_size);
    

    printf("\nThis is the encrypted buffer\n");
    print_hex_array(uint8_t_buffer, padded_buffer_size);

    AES_ctx_set_iv(&(encrypt_object), AES_init.AES_IV);

    AES_CBC_decrypt_buffer(&(encrypt_object), uint8_t_buffer,padded_buffer_size);

   // int actualDataLength = pkcs7_padding_data_length( uint8_t_buffer, padded_buffer_size, 16);
   
    printf("\nThis is the decrypted buffer\n");

    printf("the decrypted STRING in hex = ");
    
    
    print_hex_array(uint8_t_buffer, buffer_size);
    
    printf("\n");


    return 0; 
}