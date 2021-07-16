#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

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

void send_file(FILE *fp, int sockfd){
  int n;
  char data[1024] = {0};

  while(fgets(data, 1024, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, 1024);
  }
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


static FILE* file_encrypt(FILE * stream_R, long file_size, char filename)
{   FILE *stream_W;
    stream_W = fopen (filename, "rw");   //create and write to file
    if (stream_W == NULL)
     {
        fclose (stream_R);
        return -2;
     }    


    
    uint8_t buffer [file_size+1];
    if( 1!=fread( buffer , file_size, 1 , stream_R) )
     fclose(stream_R),free(buffer),fputs("entire read fails",stderr),exit(1);
    
    uint8_t ivarray[16];
    generate_iv(ivarray);
    uint8_t keyarray[16];
    generate_key(keyarray);   

    int dlen = file_size+1;
   
    //Proper Length of buffer
    int dlenu = dlen;
    if (dlen % 16) {
        dlenu += 16 - (dlen % 16);
        
    }
    
     for (int i=dlen;i<dlenu;i++) {
        buffer[i] = (uint8_t) 0;
    }
    int bufferPad = pkcs7_padding_pad_buffer( buffer, dlen, sizeof(buffer), 16 );
        

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, keyarray, ivarray);
    AES_CBC_encrypt_buffer(&ctx, buffer, dlenu);    
    AES_ctx_set_iv(&ctx,ivarray);
  
    if( 1!=fwrite( buffer , dlenu, 1 , stream_W) )
    fclose(stream_W),free(buffer),fputs("entire write fails",stderr),exit(1);

return stream_W;
}






FILE* File_Encrypt (char FileSource[1000])
{    char temp[100] = "temp";
     strcat(temp,FileSource);
         int   c;
    FILE *stream_R;
     

    stream_R = fopen (FileSource, "rw");
    if (stream_R == NULL)
        return -1;
    fseek (stream_R, 0L, SEEK_END);
    long fSize = ftell(stream_R);
    rewind(stream_R);

    //while ((c = fgetc(stream_R)) != EOF)
      //  {fputc (c, stream_W);}

    FILE * stream_W = encrypt (stream_R, fSize, temp);
    fclose (stream_R);
    

return stream_W;
    
}

int main(int argc , char *argv[])
{
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
    
        FILE* encrypted_file = File_Encrypt (file_name);       
        char temp_filename = "temp";
        strcat(temp_filename,file_name);
        FILE* fp  = fopen (temp_filename, "r"); 
        
        send_file(fp, sock);
	}
	
	close(sock);
	return 0;
}