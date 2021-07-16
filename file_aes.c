#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<errno.h> 
#include <string.h>
#include <stdint.h>
#include "pkcs7_padding.c"
#include "aes.h"
#include <time.h>

#define CBC 1 
static int test_encrypt_cbc(uint8_t buffer[], long buffer_size);

void generate_iv (uint8_t iv_array[16]);

void generate_key (uint8_t keyarray[16]);



static int test_encrypt_cbc(uint8_t buffer[], long buffer_size)
{
     
    //Initialization Vector
    uint8_t ivarray[16];
    generate_iv(ivarray);
    uint8_t keyarray[16];
    generate_key(keyarray);

                                 
    //char* report = "buffer ;
   int dlen = buffer_size;
   
    
 
    //Proper Length of buffer
    int dlenu = dlen;
    if (dlen % 16) {
        dlenu += 16 - (dlen % 16);
        
    }
    
    
       
   
    for (int i=dlen;i<dlenu;i++) {
        buffer[i] = (uint8_t) 0;
    }
                               
  
    //int bufferPad = pkcs7_padding_pad_buffer( buffer, dlen, sizeof(buffer), 16 );
        
    
    
            
    // In case you want to check if the padding is valid
    
    //start the encryption
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, keyarray, ivarray);
    
    // encrypt
    printf("the unencrypted STRING = ");
    for (int i=0; i<dlenu;i++){
        printf("%c",buffer[i]);
    }
    printf("\n");

    AES_CBC_encrypt_buffer(&ctx, buffer, dlenu);
    printf("the encrypted STRING = ");
    for (int i=0; i<dlenu;i++){
        printf("%c",buffer[i]);
    }
    printf("\n");
        
    // reset the iv !! important to work!
    AES_ctx_set_iv(&ctx,ivarray);
    
    // start decryption
    //AES_CBC_decrypt_buffer(&ctx, hexarray, dlenu);
    
    //size_t actualDataLength = pkcs7_padding_data_length( hexarray, dlenu, 16);
    
    return dlenu;
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

#define MAXBUFFER_SIZE 128




int File_Copy (char FileSource[1000], char FileDestination[1000])
{
    int   c;
    FILE *stream_R;
    FILE *stream_W; 

    stream_R = fopen (FileSource, "r");
    if (stream_R == NULL)
        return -1;
    stream_W = fopen (FileDestination, "w");   //create and write to file
    if (stream_W == NULL)
     {
        fclose (stream_R);
        return -2;
     }    
    while ((c = fgetc(stream_R)) != EOF)
        {fputc (c, stream_W);}
    
    fclose (stream_R);
    fclose (stream_W);

return 0;
    
}

void encrypt_file (char FileName[100])
{
FILE* fptr ;
uint8_t* buffer;
//uint8_t* hexarray; 

fptr =fopen(FileName, "rw");
fseek (fptr, 0L, SEEK_END);
long fSize = ftell(fptr);
rewind(fptr);

buffer = calloc(1, fSize+1);

if( 1!=fread( buffer , fSize, 1 , fptr) )
  fclose(fptr),free(buffer),fputs("entire read fails",stderr),exit(1);


// do work here, buffer is a string containing whole text 
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
   { int encrypt_size = test_encrypt_cbc(buffer,fSize);
    
    //fwrite( buffer , encrypt_size, 1 , fptr);
  //fclose(fptr),free(buffer),fputs("entire write fails",stderr),exit(1);  
   
   for (int i =0; i <encrypt_size; i++)
   {
       printf ("%c", buffer[i]); 
   }
   }

   

  




fclose(fptr);
free(buffer);
}



int main ()
{
	char message[1000];
	 srand(time(NULL)); 
	while(strcmp(message, "quit"))
	{
		printf("Enter filename with complete path you would like to send: ");
		scanf("%s" , message);
		
		printf("\n%s\n", message);

        char temp[100] = "temp";
        strcat(temp,message);

        
        File_Copy(message,temp);
        encrypt_file(temp);
    }
    

   
   



       

return 0;
}