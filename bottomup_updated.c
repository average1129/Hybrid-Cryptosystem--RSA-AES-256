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
} public_key_RSA;

typedef struct private_key_RSA {
    mpz_t n; /* Modulus */
    mpz_t e; /* Public Exponent */
    mpz_t d; /* Private Exponent */
    mpz_t p; /* Starting prime p */
    mpz_t q; /* Starting prime q */
} private_key_RSA;


typedef struct AES_parameters
{
    uint8_t[16] AES_KEY;
    uint8_t[16] AES_IV;

}AES_parameters;


typedef struct RSA_parameters
{
    public_key_RSA pub_k;
    private_key_RSA pri_k; 
} RSA_parameters;


void block_encrypt_RSA(mpz_t C, mpz_t M, public_key pub_k)// before inputtinh to function typecast C & M to mpz_t 
{
    /* C = M^e mod n */
    mpz_powm(C, M, pub_k.e, pub_k.n); 
    return;
}

void block_decrypt_RSA(mpz_t M, mpz_t C, private_key pri_k)
{
    mpz_powm(M, C, pri_k.d, pri_k.n); 
    return;
}

void generate_large_prime(mpz_t* r_number)
{
    int rndBit=1023; 					// bound for mpz_randb
	
	gmp_randstate_t random_state; // random generator state object    	
	 
	gmp_randinit_default(random_state); // initilize random state with default algorithm 	
		
	//defining seed with unsigned long before beginning 
	unsigned long seed = (unsigned long)(time(NULL));	
	
	gmp_randseed_ui(random_state, seed);

	   
    mpz_urandomb(*r_number, random_state, rndBit);
    	
	int odd_check = mpz_odd_p (*r_number); 		// returns non zero if odd 
	if (odd_check==0) 							// if result is zero, that is term is even -> enter if condition 
	{
		unsigned long int one =1;
		mpz_add_ui ( *r_number, *r_number, one);  // now r_number is odd 
	}
	
	int reps= 40 ; // number of times to run primality test;
	mpz_t prime_1024;
	mpz_init (prime_1024);
	
	int primality_test = mpz_probab_prime_p (*r_number,  reps); //Return 2 if n is definitely prime, 	
													//return 1 if n is probably prime (without being certain), or return 0 if n is definitely non-prime.
		
	if(primality_test!=2)
	{
		mpz_nextprime (*r_number, *r_number);	
		//primality_test =  mpz_probab_prime_p (r_number,  reps);
	}	
	mpz_t tmp; mpz_init(tmp);
    mpz_t local_e; mpz_init(local_e); mpz_set_ui(local_e, 65537);

	mpz_mod(tmp, *r_number, local_e);        /* If p mod e == 1, gcd(phi, e) != 1 */
    while(!mpz_cmp_ui(tmp, 1))         
    {
        mpz_nextprime(*r_number, *r_number);    /* so choose the next prime */
        mpz_mod(tmp2, *r_number, local_e);
    }
	

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

mpz_set(pub_k.e, pri_k.e);
mpz_set(pub_k.n, pri_k.n);


return;
} 


void generate_private_key (private_key pri_k)
{   mpz_init(pri_k.p);
    mpz_init(pri_k.q);
    mpz_init(pri_k.n);
    mpz_init(pri_k.e);
    mpz_init(pri_k.d);
    mpz_set_ui(pri_k.e, 65537 );
	
	mpz_t phi; mpz_init(phi);
    mpz_t tmp1; mpz_init(tmp1);
    mpz_t tmp2; mpz_init(tmp2);
 
    mpz_t * prime_p_ptr = & (pri_k.p);
    mpz_t * prime_q_ptr;= & (pri_k.q);

    generate_large_prime (prime_p_ptr);
    generate_large_prime (prime_q_ptr);
    while (mpz_cmp(*prime_p_ptr, *prime_q_ptr) == 0){
        generate_large_prime (prime_q_ptr);
    }    

    mpz_mul(pri_k.n, pri_k.p, pri_k.q);

	mpz_sub_ui(tmp1, pri_k.p, 1);
    mpz_sub_ui(tmp2, pr_k.q, 1);
    mpz_mul(phi, tmp1, tmp2);

	if(mpz_invert(.pri_k.d, pri_k.e, phi) == 0)
	{
		printf("Invert Failed");
	}
return;
}

AES_parameters initialize_AES()
{
    AES_parameters new_parameters;
    generate_key(new_parameters.AES_KEY);
    generate_iv (new_parameters.AES_IV); 
    
	return new_parameters;
}

RSA_parameters initialize_RSA()
{
    RSA_parameters new_parameters ;


    generate_private_key (new_paramters.pri_k);
    generate_public_key (new_parameters.pub_k, new_parameters. pri_k);
    
	return new_parameters;
}

AESkey_encrypt_RSA(uint8_t aes_key[16], RSA_parameters RSA_initialization)
{ 
mpz_t M;
mpz_init(M);
mpz_import(M, sizeof(aes_key), 1, sizeof(aes_key[0]), 0, 0, input);
mpz_t C;
mpz_init(C);
block_encrypt_RSA(C,M,RSA_initialization.pub_k);
return;}

void encrypt_file (char filename[], crypt Encrypted_Data)
{
 srand(time(NULL));
 AES_parameters AES_initial = initialize_AES();
 RSA_parameters RSA_initial = initialize_RSA(); 
 AESkey_encrypt_RSA(AES_parameters.AES_KEY, RSA_initial,);// add a string here to store encrypted AES key
 // open file, copy file into buffer
 // encrypt buffer with AES 
FILE* stream_R = fopen (filename, "r");
    if (stream_R == NULL)
        printf("file read error");

fseek (stream_R, 0L, SEEK_END);
    long fSize = ftell(stream_R);
    rewind(stream_R);

uint8_t buffer [file_size+1];
    if( 1!=fread( buffer , file_size, 1 , stream_R) )
     fclose(stream_R),free(buffer),fputs("entire read fails",stderr),exit(1);


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
