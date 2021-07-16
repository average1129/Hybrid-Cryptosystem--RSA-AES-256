#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CBC 1

#include "aes.h"
#include "pkcs7_padding.c"
//#include "padding.h"


void input_data(char* in_buf);



static void test_encrypt_cbc(void);
uint8_t* generate_IV(uint8_t * IV_ptr);
char* generate_KEY(char * KEY_ptr);
	
	
int main(void)
{
    int exit=0;

#if defined(AES256)
    printf("\nTesting AES256\n\n");
#elif defined(AES192)
    printf("\nTesting AES192\n\n");
#elif defined(AES128)
    printf("\nTesting AES128\n\n");
#else
    printf("You need to specify a symbol between AES128, AES192 or AES256. Exiting");
    return 0;
#endif

    test_encrypt_cbc();

    return exit;
}


void input_data(char* in_buf)
{	
	
	printf("enter message to encrypt:")
	scanf (%s, in_buf);
	
}

uint8_t* generate_IV(uint8_t * IV_ptr)
{

uint8_t *  i;
uint8_t k;


	for (i = IV_ptr; i <IV_ptr+16; i++)
{
     k = rand()%256;
      *(IV_ptr+i) = k ;
}
	
return IV_ptr;}

char* generate_KEY(char * KEY_ptr)
{

uint8_t *  i;
uint8_t k;
 // move this to main 

	for (i = KEY_ptr; i <KEY_ptr+16; i++)
{
     k = rand()%256;
     *(KEY_ptr+i) = k;
}
	
return KEY_ptr;}

static void test_encrypt_cbc(void)
{	
	srand(time(NULL));
    //Initialization Vector
  	  
	uint8_t * IV_ptr = (uint8_t *)calloc(16,sizeof(uint8_t)); 
		
	IV_ptr = generate_IV(IV_ptr); 
	
	uint8_t * KEY_ptr= (uint8_t *)calloc(16,sizeof(uint8_t)); 

	KEY_ptr = generate_KEY(KEY_ptr);
	
                                   
    //char* report = "my super secret thing that needs to remain that way!";
    //char* key = "thisIstheKey"; // insert function for key generation 
  
    //int klen = strlen(key);
    
	string in_buf[100];
	input_data(in_buf);
	int dlen = strlen(in_buf);
	
    printf("THE PLAIN TEXT STRING = ");

	for (i=0; i<dlen;i++){
        printf("%c", in_buf[i]);
    }
    printf("\n");
    
   
    //Proper Length of report
    int dlenu = dlen;
    if (dlen % 16) {
        dlenu += 16 - (dlen % 16);
        printf("The original length of the STRING = %d and the length of the padded STRING = %d\n", dlen, dlenu);
    }
    
    uint8_t in_buf_array[dlenu];
	memset( in_buf_array, 0, dlenu );
	for (int i=0;i<dlen;i++) {
        in_buf_array[i] = (uint8_t)in_buf[i];
    }
	
    int in_buf_Pad = pkcs7_padding_pad_buffer( in_buf_array, dlen, sizeof(in_buf_array), 16 );
	
	printf("The padded STRING  is = ");
    for (i=0; i<dlenu;i++){
        printf("%c",in_buf_array[i]);
    }
    printf("\n");

	int valid = pkcs7_padding_valid( in_buf_array, dlen, sizeof(in_buf_arrayarray), 16 );
	
	 printf("Is the pkcs7 padding valid  report = %d ", valid);

	
    //start the encryption
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, *KEY_ptr, *IV_ptr);
    
    // encrypt
    AES_CTR_xcrypt_buffer(&ctx, in_buf_array, dlenu);
    printf("the encrypted STRING = ");
    for (i=0; i<dlenu;i++){
        printf("%c",in_buf_array[i]);
    }
    printf("\n");
        
    // reset the iv !! important to work!
    AES_ctx_set_iv(&ctx,*IV_ptr);
    
    // start decryption
    AES_CTR_xcrypt_buffer(&ctx, in_buf_array, dlenu);
    
    size_t actualDataLength = pkcs7_padding_data_length( in_buf_array, dlenu, 16);
    printf("The actual data length (without the padding) = %ld\n", actualDataLength);
    
    printf("the decrypted STRING = ");
    for (i=0; i<actualDataLength;i++){
        printf("%c",in_buf_array[i]);
    }
    printf("\n");
}