#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include "list.h"
#include "list.c"

#define MAXSIZE 1000

// SPECIAL CHARACTER TO TERMINATE THE s-talk is '!'

struct hostent* host;  // Need for host address.
char* senderbuffer; // remote person
char recieverbuffer[MAXSIZE]; // loacl person
int n_socket;
int localPort;


struct sockaddr_in local,remote;

struct LIST *remotelist;          // list store messages from Remote person
struct LIST* locallist;        // list store our own messages 

sem_t semaphore_mutex; // Need semiphore For critical section problem.

void * Sender()   
{
      for(;;)    // infinte loop for threading to run until special characters recieved
        { 
            int break1=1;
            if(locallist->first!=NULL)
            {
                sem_wait(&semaphore_mutex); // wait 
                senderbuffer=ListFirst(locallist); 

                int n=sendto(n_socket, (const char *)senderbuffer, MAXSIZE,  MSG_CONFIRM, (const struct sockaddr *) &remote, sizeof(remote)); 

                if (n < 0) 
                {
                    printf("ERROR: Failed to send Message\n");
                    printf("ERROR: User Already Left\n");
                }      
                ListRemove(locallist);
                sem_post(&semaphore_mutex); // release 
                break1= strncmp("!",senderbuffer,1);
            }
            if(break1==0)
            {
                exit(0);   
            } 
        }   
        pthread_exit(NULL);                               
}
void * Reciever(){

    for(;;)    // infinte loop for threading to run until special characters recieved
    { 
        int len=sizeof(remote);   
        int n = recvfrom(n_socket, (char *)recieverbuffer, MAXSIZE, MSG_WAITALL, (struct sockaddr*) &remote, &len);	  
	    if (n < 0) 
        {
           printf("ERROR: Failed to recieve Message\n");
           
        }
        
        sem_wait(&semaphore_mutex);  // wait
        ListADD(remotelist,&recieverbuffer);
        sem_post(&semaphore_mutex); //release
        
        if(strncmp("!",recieverbuffer,1)==0)
        {

            pthread_exit(NULL);// Don not need this thread anymore
            break;
        }    
    }                              
}

void * UserMessage(){    // store message by ourself.
    
    for(;;)      // infinte loop for threading to run until special characters recieved
    {
        char* message=fgets(recieverbuffer,MAXSIZE,stdin);
        sem_wait(&semaphore_mutex);  // wait
        ListADD(locallist,message);
        sem_post(&semaphore_mutex); //release

        if(strncmp("!",message,1)==0)  // Session Terminated by local
        {
            
            break; 
        } 
    }
	pthread_exit(NULL); // Don't need this Thread anymore.
}


void * PrintMessage(){  // print message of Remote person and then take of that message from the list.
    
    for(;;)  // infinte loop for threading to run until special characters recieved
    {
        int break2=1;
        if(remotelist->count!=0)  // if list empty then nothing to print
        {
            sem_wait(&semaphore_mutex);  // wait
	        char *first=ListFirst(remotelist);
            
	        printf("Remote: %s\n",first);
            int len=strlen(first);
            ListRemove(remotelist);
            sem_post(&semaphore_mutex); //release
            break2=strncmp("!",first,1);
        }  
        if(break2==0)
        {
            printf("Session Terminated Gud Bye\n");
            sem_post(&semaphore_mutex); //release
            close(n_socket);
        //    ListFree(locallist,locallist->current);
        //    ListFree(remotelist,remotelist->current);
            pthread_exit(NULL);
            exit(0);
        }
    }
}

int main(int argc, char *argv[]){

    pthread_t thread[4];  //  Created 4 threads
    remotelist=ListCreate();  // remote messages stored in list 
    locallist=ListCreate();   // local messages stored in list
    
    if (argc != 4) {
         printf("Information provided is not sufficient\n");
         exit(1);
     }
    n_socket= socket(AF_INET, SOCK_DGRAM, 0);    // Creating a socket

    if(n_socket==-1){
        printf("socket Creation Error\n");
        exit(1);
    }
    memset(&remote, 0, sizeof(remote)); // If remote memory is not empty then making it 0.
    memset(&local, 0, sizeof(local));  // If local memory is not empty then making it 0.

//Remote Information stored in struct sockaddr_in
    int remotePort= atoi(argv[3]);  
    char *remoteName= argv[2];

    remote.sin_family = AF_INET; 
    remote.sin_port = htons(remotePort); 
    if((host =gethostbyname(remoteName)) ==0)
    {
        printf("gethostbyname failed");
	exit(0);
    }
    else{
        memcpy((void*)&remote.sin_addr,host->h_addr_list[0],host->h_length); 
    }
 
// Local Information

    localPort= atoi(argv[1]);  // store local port info through argv[1]

    local.sin_family = AF_INET;  
    local.sin_port = htons(localPort); 
    local.sin_addr.s_addr= INADDR_ANY;   // assign any address, does not need to specify
 
    if (bind(n_socket, (struct sockaddr *) &local,sizeof(local)) < 0) 
        printf("ERROR on binding\n");

    sem_init(&semaphore_mutex,0,1);  // Mutex initalized for critical section problem

    pthread_create(&thread[0],NULL,Reciever,NULL);  // reciever message.
    pthread_create(&thread[1],NULL,Sender,NULL);   // sender message.
    pthread_create(&thread[2],NULL,UserMessage,NULL);  // store message by ourself.
    pthread_create(&thread[3],NULL,PrintMessage,NULL);  // print message recieve from other user
    
    pthread_exit(NULL);

    sem_destroy(&semaphore_mutex);   // Mutex destroyed
    return 0;
}
