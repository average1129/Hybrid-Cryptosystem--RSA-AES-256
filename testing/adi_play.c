#include <stdio.h>
#include "aes.h"
#include <time.h>
#include <string.h>

// include fork with pkcs_padding.c and pkcs_padding.h

#define CBC 1 

char* generate_IV()
{
//malloc 
uint8_t IV[16];
//char buf[2];
uint8_t i, k;
srand(time(NULL)); // move this to main 

	for (i = 0; i <16; i++)
{
     k = rand()%256;
     IV[i] = k;
}
	
return IV;}

char* generate_key ()
{
//malloc here 
uint8_t KEY[16];
//char buf[2];
uint8_t i, k;
srand(time(NULL));

	for (i = 0; i <16; i++)
{
     k = rand()%256;
     KEY[i] = k;
}
}

void String_Formatting(char* input_string)
{
	int string_len = strlen(input_string);
	int string_len_u = string_len;
	
	if (string_len%16)
	{
		string_len_u+= (16-(string_len%16));
	}
	
uint8_t input_string_array[string_len_u];
memset(input_string_array,0,string_len_u);

	for (int i =0;i < string_len; i++)
	{
		input_string_array = (uint8_t)input_string[i]; // array holding data to be encrypted 
	}

int input_string_pad = pkcs7_padding_pad_buffer( input_string_array, string_len, sizeof(input_string_array), 16 );

}

int main()
{
//start the encryption
struct AES_ctx ctx;
AES_init_ctx_iv(&ctx, kexarray, iv);
    
// encrypt
AES_CBC_encrypt_buffer(&ctx, input_string_array, string_len_u);
}

// reset the iv !! important to work!
AES_ctx_set_iv(&ctx,iv);

// start decryption
AES_CBC_decrypt_buffer(&ctx, hexarray, dlenu);

size_t actualDataLength = pkcs7_padding_data_length( hexarray, dlenu, 16);

printf("the decrypted STRING = ");
for (i=0; i<actualDataLength;i++){
    printf("%02x",hexarray[i]);
}
printf("\n");

