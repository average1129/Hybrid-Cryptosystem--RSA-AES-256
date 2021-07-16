#include <stdio.h>
#include "aes.h"
#include <time.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "pkcs7_padding.c"



#define CBC 1 
static void test_encrypt_cbc(void);

void generate_iv (uint8_t iv_array[16]);

void generate_key (uint8_t keyarray[16]);

int main(void)
{
    srand(time(NULL)); 
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
    for (int i=0; i <10; i++)
    {test_encrypt_cbc();}

    return exit;
}


static void test_encrypt_cbc(void)
{
     


    //Initialization Vector
    uint8_t ivarray[16];
    generate_iv(ivarray);
    uint8_t keyarray[16];
    generate_key(keyarray);

                                 
    char* report = "my super secret thing that needs to remain that way!";
   int dlen = strlen(report);
   
    
    printf("THE PLAIN TEXT STRING = ");
    for (int i=0; i<dlen;i++){
        printf("%c", report[i]);
    }
    printf("\n");
    
   
    //Proper Length of report
    int dlenu = dlen;
    if (dlen % 16) {
        dlenu += 16 - (dlen % 16);
        printf("The original length of the STRING = %d and the length of the padded STRING = %d\n", dlen, dlenu);
    }
    
    
       
    // Make the uint8_t arrays
    uint8_t hexarray[dlenu];
    
    
    // Initialize them with zeros
    memset( hexarray, 0, dlenu );
    
    
    // Fill the uint8_t arrays
    for (int i=0;i<dlen;i++) {
        hexarray[i] = (uint8_t)report[i];
    }
                               
  
    int reportPad = pkcs7_padding_pad_buffer( hexarray, dlen, sizeof(hexarray), 16 );
        
    printf("The padded STRING in hex is = ");
    for (int i=0; i<dlenu;i++){
        printf("%02x",hexarray[i]);
    }
    printf("\n");
    
            
    // In case you want to check if the padding is valid
    int valid = pkcs7_padding_valid( hexarray, dlen, sizeof(hexarray), 16 );
    //int valid2 = pkcs7_padding_valid( kexarray, klen, sizeof(kexarray), 16 );
    printf("Is the pkcs7 padding valid  report = %d", valid);
    
    //start the encryption
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, keyarray, ivarray);
    
    // encrypt
    AES_CBC_encrypt_buffer(&ctx, hexarray, dlenu);
    printf("the encrypted STRING = ");
    for (int i=0; i<dlenu;i++){
        printf("%02x",hexarray[i]);
    }
    printf("\n");
        
    // reset the iv !! important to work!
    AES_ctx_set_iv(&ctx,ivarray);
    
    // start decryption
    AES_CBC_decrypt_buffer(&ctx, hexarray, dlenu);
    
    size_t actualDataLength = pkcs7_padding_data_length( hexarray, dlenu, 16);
    printf("The actual data length (without the padding) = %ld\n", actualDataLength);
    
    printf("the decrypted STRING in hex = ");
    for (int i=0; i<actualDataLength;i++){
        printf("%02x",hexarray[i]);
    }
    printf("\n");
}

void generate_iv (uint8_t iv_array[16])
{	
	memset( iv_array, 0, 16 );
	
	for (int i =0; i<16; i++)
	{
		iv_array[i] = rand()%256;

	}
    for (int i = 0; i<16; i++)
    {
        printf( "%02x", iv_array[i]);
    }
    printf ("\n");
//return &iv_array;
}

void generate_key (uint8_t keyarray[16])
{
	memset( keyarray, 0, 16 );
	
	for (int i =0; i<16; i++)
	{
		keyarray[i] = (uint8_t)rand()%256;

	}

    for (int i = 0; i<16; i++)
    {
        printf( "%02x", keyarray[i]);
    }
    printf ("\n");
//return &keyarray;
}
