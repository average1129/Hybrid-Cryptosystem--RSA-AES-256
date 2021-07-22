int main()
{

int sock;
	struct sockaddr_in server;
  // add functionality to input IP address to connect to 
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

//printf ("Enter file name:");

char file_name[100];

//scanf("%s", file_name);

//FILE* fptr ; malloc 
	
	//keep communicating with server
	while(strcmp(file_name, "quit"))
	{
    printf("Enter file name to send : ");
		scanf("%s" , file_name);
		Crypt input_File;
		Crypt * input_File = &(input_File);
        FILE_READ(file_name,input_File);  // file contents have been written into uint8_t buffer 
         
        
        
	}
	
	close(sock);
	return 0;
}



return 0;
}


