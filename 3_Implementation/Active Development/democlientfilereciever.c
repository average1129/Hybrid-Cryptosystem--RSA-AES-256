#include <stdio.h>
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
//#include "pkcs7_padding.c"
#include "aes.h"
#include "RSA.h"
#include <time.h>

#define SIZE 1600

// generate RSA public key and transmit to sender client
int main (){

char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

  if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		perror("[-]Error in listening");
    exit(1);
	}

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  //write_file(new_sock); replace with functionalities
  // do all appropriate initialiizations 
  
   RSA_parameters  reciever_RSA_setup;
   initialize_RSA(&reciever_RSA_setup); // rsa public and private key have now been created 
                                        // simply share keys 
   generate_private_key(&(reciever_RSA_setup.pri_k));
   generate_public_key(&(reciever_RSA_setup.pub_k),&(reciever_RSA_setup.pri_k));
   
    //char* tmp3 = mpz_get_str(NULL,10,reciever_RSA_setup.pub_k.n);
    //printf ("This is n : %s \n", tmp3);
    
    char* tmp4 = mpz_get_str(NULL,10,reciever_RSA_setup.pub_k.e);
    printf ("This is e: %s \n", tmp4);

//  int send_status = send(new_sock, (char *)&(tmp3), strlen(tmp3), 0);
  int send_status = send(new_sock, (char *)&(tmp4), strlen(tmp4), 0);

  printf("send status %d", send_status);
  //printf("[+]Data written in the file successfully.\n");

  return 0;
}