#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<errno.h> 
#include <string.h>

#define MAXBUFFER_SIZE 128


// user will write a message;
// if message crosses encryption //length we will fragment it and //zeropad

// if time permits we can apply same //concept to file systems 

//seperate thread can be used for file transmissions

int File_Copy (char FileSource [], char FileDestination [])
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
        fputc (c, stream_W);
    fclose (stream_R);
    fclose (stream_W);

    return 0;
}

launch_file(const char* filename )
{//create a copy of file to be outputted in sending folder
	FILE *fptr;
    if ((fptr = fopen(*filename,, "r")) == NULL) {
        printf("Error! File cannot be opened.");
        exit(1);
    }
}
{
	
}
int main ()
{
	char message[1000];
	
	while(strcmp(message, "quit"))
	{
		printf("Enter filename with complete path you would like to send: ");
		scanf("%s" , message);
		
		printf("\n%s\n", message);
	}		
return 0;
}