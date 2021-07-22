#include <stdio.h>
#include <time.h>

#include "aes.h"
#include "pkcs7_padding.h"
#include "AES_functions.h"
#include "RSA.h"
#include "filefunctions.h"
#include <gmp.h>

int main()
{
    char name[100];
    Crypt File_encryption_object;
    initialize_Crypt(&File_encryption_object);
    
    
    printf("Enter filename: \n");
    scanf("%s", name);
   

    char* tmp = mpz_get_str(NULL,10,File_encryption_object.Crypt_RSA_parameters.pri_k.d);
    printf ("This is d : %s \n", tmp);

    char* tmp1 = mpz_get_str(NULL,10,File_encryption_object.Crypt_RSA_parameters.pri_k.p);
    printf ("This is p : %s \n", tmp1);

   char* tmp2 = mpz_get_str(NULL,10,File_encryption_object.Crypt_RSA_parameters.pri_k.q);
    printf ("This is q : %s \n", tmp2);

    char* tmp3 = mpz_get_str(NULL,10,File_encryption_object.Crypt_RSA_parameters.pri_k.n);
    printf ("This is n : %s \n", tmp3);
    
    char* tmp4 = mpz_get_str(NULL,10,File_encryption_object.Crypt_RSA_parameters.pri_k.e);
    printf ("This is e: %s \n", tmp4);
    

   /* decrypt_AES_key(&new_RSA_setup,&secret,&secret_revealed);
    char* tmp9 = mpz_get_str(NULL,10,secret_revealed.M);
    printf ("This is the decrypted AES key: %s \n", tmp9);
    */ 
    
    READ_FILE(name, &File_encryption_object);
    printf("This is the contents of the file");
    print_hex_array(File_encryption_object.write_buffer, File_encryption_object.padded_buffer_Size); printf("\n");

    encrypt_Crypt(&File_encryption_object);

    printf("This is the contents of the file after encryption");
    print_hex_array(File_encryption_object.write_buffer, File_encryption_object.padded_buffer_Size); printf("\n");

     

    char* tmp5 = mpz_get_str(NULL,10,File_encryption_object.Crypt_message.M);
    printf ("This is the AES key passed to be encrypted: %s \n", tmp5);

    char* tmp6 = mpz_get_str(NULL,10,File_encryption_object.Crypt_message.C);
    printf ("This is encrypted AES key: %s \n", tmp6);



}
