// C program for the Server Side

// inet_addr
#include <arpa/inet.h>

// For threading, link with lpthread
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Semaphore variables
sem_t x, y;
pthread_t tid;
pthread_t clientthreads[100];
int readercount = 0;










#define MAX 80
#define PORT 8000
#define SA struct sockaddr


struct contact
{

    long ph;

    char name[20],add[20],email[30],fun_name[20];

}list,ll1,sort;

FILE *fp, *ft;

int i,n,ch,l,found;


void sort_the_file()
{



for(i=97; i<=122; i=i+1)

        {

             fp=fopen("contact.dll","r");
              if ( fp == NULL )
		    {
			printf( "file failed to open." ) ;
		    }
	     ft=fopen("temp.dat","w");
	     if ( ft == NULL )
		    {
			printf( "file failed to open." ) ;
		    }

            fflush(stdin);

            found=0;

            while(fread(&sort,sizeof(sort),1,fp)==1)

            {

                if(sort.name[0]==i || sort.name[0]==i-32)

                {

                   fwrite(&sort,sizeof(sort),1,ft);

                }

            }

            

           	fclose(fp);

		fclose(ft);

		remove("contact.dll");

		rename("temp.dat","contact.dll");

        }


}




void send_file_display(int sockfd)
{		

			
		fp=fopen("contact.dll","r");
		if ( fp == NULL )
		    {
			printf( "file failed to open." ) ;
		    }
 	while(fread(&list,sizeof(list),1,fp)==1)

            {
            	
            	if(send(sockfd,&list,sizeof(list),0) == -1)
            	{
            			printf("file not send sucessfully");
		}
            }
            strcpy(ll1.name,"exit");
            send(sockfd,&ll1,sizeof(ll1),0);
            fclose(fp);
            
           
            

return;
}


void send_file_searched(int sockfd , long search_ph)
{
	 
	    
	    fp=fopen("contact.dll","r");
	    if ( fp == NULL )
		    {
			printf( "file failed to open." ) ;
		    }

            struct contact sort;
             strcpy(sort.fun_name,"notfound");

            while(fread(&list,sizeof(list),1,fp)==1)

            {

               
			
                if(list.ph == search_ph)

                {
				
                   	send(sockfd,&list,sizeof(list),0);
                   	 strcpy(sort.fun_name,"found");
                   	 break;
			
                    

                }
                

            }
            
            strcpy(ll1.name,"exit");
            send(sockfd,&ll1,sizeof(ll1),0);
            fclose(fp);
            
            send(sockfd,&sort,sizeof(sort),0);
            
            
            
            

          


}

void send_file_edit(int sockfd)
{


			
		// Lock the semaphore
    		sem_wait(&x);				
		bool chk=false;
		 fp=fopen("contact.dll","r");
		 if ( fp == NULL )
		    {
			printf( "file failed to open." ) ;
		    }
		  ft=fopen("temp.dat","w");
		  if ( ft == NULL )
		    {
			printf( "file failed to open." ) ;
		    }

            strcpy(sort.fun_name,"notfound");

            while(fread(&list,sizeof(list),1,fp)==1)

            {

               
			
                if(ll1.ph != list.ph)
                {
			fwrite(&list,sizeof(list),1,ft);
		 }
		 else
		 {
		 	chk=true;
		 	strcpy(sort.fun_name,"Edited");
		 }
		  
		  
                

            }
            if(chk==true)
            {
		fwrite(&ll1,sizeof(ll1),1,ft);   
		
		}
        
        fclose(fp);

        fclose(ft);

        remove("contact.dll");

        rename("temp.dat","contact.dll");
        
        send(sockfd,&sort,sizeof(sort),0);
        // Unlock the semaphore
    		sem_post(&x);
            
return;

}



void send_file_delete(int sockfd)
{


		struct contact sort;
		 fp=fopen("contact.dll","r");
		 if ( fp == NULL )
		    {
			printf( "file failed to open." ) ;
		    }
		  ft=fopen("temp.dat","w");
		  if ( ft == NULL )
		    {
			printf( "file failed to open." ) ;
		    }
		 
		 strcpy(sort.fun_name,"notfound");
            

            while(fread(&list,sizeof(list),1,fp)==1)

            {

               
			
                if(ll1.ph !=list.ph)
                {
			fwrite(&list,sizeof(list),1,ft);
		 }else{
		 strcpy(sort.fun_name,"found");
		 }
                

            }
        
        
        fclose(fp);

        fclose(ft);

        remove("contact.dll");

        rename("temp.dat","contact.dll");
        
       
         send(sockfd,&sort,sizeof(list),0);
          
return;

}
bool send_file_add(int sockfd,struct contact demo)
{
				
				
				
				fp=fopen("contact.dll","r");
				if ( fp == NULL )
		    {
			printf( "file failed to open." ) ;
		    }

           

            while(fread(&ll1,sizeof(ll1),1,fp)==1)

            {

               
			
                if(ll1.ph == demo.ph)

                {
                	fclose(fp);
                   	 return true;
                }
                

            }
            
             fclose(fp);
            
           		
	return false;			
				
}

// Function designed for chat between client and server.
void* func(void* args)
{
	int sockfd = *((int*)args);
		for(;;)
	
		{
		
		
		recv(sockfd,&list, sizeof(list),0);
		
			if(strcmp(list.fun_name,"add")==0)
			{
				
					if(send_file_add(sockfd,list) == 0)
					{
					 struct contact sort;
					fp=fopen("contact.dll","a");
					if ( fp == NULL )
					{
					printf( "file failed to open." ) ;
					}
					
					fwrite(&list,sizeof(list),1,fp);
					fclose(fp);
					strcpy(sort.fun_name,"added");
					send(sockfd,&sort,sizeof(sort),0);	
					}
					else
					{
					strcpy(sort.fun_name,"notadded");
					send(sockfd,&sort,sizeof(sort),0);	
					}
            
           
           				
			}

				
				
				
				
				
						
			
			
			if(strcmp(list.fun_name,"display")==0)
       		 {
					
					send_file_display(sockfd);
					
					
			 }
			
			if(strcmp(list.fun_name,"search")==0)
       		 {
       		 		
					
					
					send_file_searched(sockfd,list.ph);
					
					
			 }
			 
			 
			if(strcmp(list.fun_name,"edit")==0)
       		 {
					
					
					
       		 		ll1=list;
       		 		
					send_file_edit(sockfd);
					
					
					
					
					
			 }
			 
			 
			 if(strcmp(list.fun_name,"delete")==0)
       		 {
					
					
       		 		ll1=list;
					
					send_file_delete(sockfd);
					
					
			 }
			 
			 
			 if(strcmp(list.fun_name,"exit")==0)
       		 {
       		 	pthread_exit(NULL);
       		 	return 0;
       		 }
				
        }
		
		pthread_exit(NULL);

	return 0;
	}	
	










// Driver Code
int main()
{
	// Initialize variables
	int serverSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;

	socklen_t addr_size;
	sem_init(&x, 0, 1);
	sem_init(&y, 0, 1);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8989);

	// Bind the socket to the
	// address and port number.
	bind(serverSocket,
		(struct sockaddr*)&serverAddr,
		sizeof(serverAddr));

	// Listen on the socket,
	// with 40 max connection
	// requests queued
	if (listen(serverSocket, 50) == 0)
		printf("Listening\n");
	else
		printf("Error\n");

	// Array for thread
	pthread_t tid[60];

	int i = 0;

	while (1) {
		addr_size = sizeof(serverStorage);

		// Extract the first
		// connection in the queue
		newSocket = accept(serverSocket,
						(struct sockaddr*)&serverStorage,
						&addr_size);
						
					
			if (pthread_create(&clientthreads[i++], NULL,
							func, &newSocket)
				!= 0)
				{

				// Error in creating thread
				printf("Failed to create thread\n");
				}
		
	
			
		}
	

	return 0;
}

