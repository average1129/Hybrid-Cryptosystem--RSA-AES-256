#include <stdio.h>
#include <time.h>
#include "RSA.h"

int main()
{   srand(time(NULL));
    uint8_t AES_key[16];
    generate_AES_key(AES_key);
    
    printf("This is the randomly generated AES key:");
    for (int i =0; i<16; i++)
    {        printf("%u", AES_key[i] );
    }
    printf("\n");

    RSA_parameters new_RSA_setup;
    initialize_RSA(&new_RSA_setup);
    
    message secret;
    message secret_revealed;
    initialize_message(&secret);
    initialize_message(&secret_revealed);
    encrypt_AES_key(AES_key, &new_RSA_setup,&secret);

    char* tmp5 = mpz_get_str(NULL,10,secret.M);
    printf ("This is the AES key passed to be encrypted: %s \n", tmp5);

    char* tmp6 = mpz_get_str(NULL,10,secret.C);
    printf ("This is encrypted AES key: %s \n", tmp6);

    

    char* tmp = mpz_get_str(NULL,10,new_RSA_setup.pri_k.d);
    printf ("This is d : %s \n", tmp);

     char* tmp1 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.p);
    printf ("This is p : %s \n", tmp1);

   char* tmp2 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.q);
    printf ("This is q : %s \n", tmp2);

    char* tmp3 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.n);
    printf ("This is n : %s \n", tmp3);
    
    char* tmp4 = mpz_get_str(NULL,10,new_RSA_setup.pri_k.e);
    printf ("This is e: %s \n", tmp4);
    

    decrypt_AES_key(&new_RSA_setup,&secret,&secret_revealed);
    char* tmp9 = mpz_get_str(NULL,10,secret_revealed.M);
    printf ("This is the decrypted AES key: %s \n", tmp9);

    
    return 0; 
}
