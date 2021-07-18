#include <stdio.h>
#include <time.h>
#include <string.h>
#include <gmp.h> // include header 
#include <stddef.h>
#include "pkcs7_padding.c"
#include "aes.h"

#define CBC 1

//open a socket (bidirectional), first unidirectional  // first for send seperately
//then reception socket // then develop dual threaded 
// copy a file contents into buffer 
// encrypt buffer using aes 
//encrypt buffer keys using rsa 
//send rsa public keys
//send encrypted aes key 
// send encrypted data 

//not so sure if this function will be void, cant figure out return value
typedef struct public_key_RSA {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
} public_key;

typedef struct private_key_RSA {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
    mpz_t d; /* Private Exponent */
    mpz_t p; /* Starting prime p */
    mpz_t q; /* Starting prime q */
} private_key;


typedef struct AES_parameters
{
    uint8_t[16] AES_KEY;
    uint8_t[16] AES_IV;

}AES_parameters;

generate_large_prime

typedef struct RSA_parameters
{
    public_key_RSA pub_k;
    private_key_RSA pri_k; 
} RSA_parameters;


void generate_large_prime(mpz_t prime)
{

}
void generate_key(uint8_t key_array[16])
{
memset( keyarray, 0, 16 );
	
	for (int i =0; i<16; i++)
	{
		keyarray[i] = (uint8_t)rand()%256;

	}

}

void generate_iv (uint8_t iv_array[16])
{
memset( iv_array, 0, 16 );
	
	for (int i =0; i<16; i++)
	{
		iv_array[i] = rand()%256;

	}
}

void generate_public_key (public_key pub_k,private_key pri_k)
{

pz_init(pub_k.n);
mpz_init(pub_k.e); 
} 

void generate_private_key (private_key pri_k)
{   mpz_init(pri_k.p);
    mpz_init(pri_k.q);
    mpz_init(pri_k.n);
    mpz_init(pri_k.e);
    mpz_init(pri_k.d);
    mpz_set_ui(pri_k.e, 65537 );
    mpz_t * prime_p_ptr = & (pri_k.p);
    mpz_t * prime_q_ptr;= & (pri_k.q);

    generate_large_prime (pri_k.p);
    generate_large_prime (pri_k.q);
    
}
AES_parameters initialize_AES()
{
    AES_parameters new_parameters;
    generate_key(new_parameters.AES_KEY);
    generate_iv (new_parameters.AES_IV); 
    
}

RSA_parameters initialize_RSA()
{
    RSA_parameters new_parameters ;


    generate_private_key (new_paramters.pri_k);
    generate_public_key (new_parameters.pub_k, new_parameters. pri_k);
    
}


void encrypt_file (char filename[], crypt Encrypted_Data)
{
 srand(time(NULL));
 AES_parameters AES_initial = initialize_AES();
 RSA_parameters RSA_initial =  initialize_RSA(); 
} 
int main()
{

srand(time(NULL)); 
int sock;
	struct sockaddr_in server;
	char file_name[1000] , server_reply[2000];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	// add option for client to input ip address of client he wants to send file to 

	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	server.sin_family = AF_INET;
	server.sin_port = htons( 8879 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
	
	//keep communicating with server
	while(strcmp(file_name, "quit"))
	{
        printf("Enter file name to send : ");
		scanf("%s" , file_name);
        struct crypt Encrypted_File;
        encrypt_file(file_name, Encrypted_File);
        send_file(fp, sock);
	}
	
	close(sock);
	return 0;
}
