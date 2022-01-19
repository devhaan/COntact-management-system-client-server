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

// MACROS DEFINITIONS
#define MAX 80
#define PORT 8000
#define SA struct sockaddr

// Semaphore variables
sem_t x, y;

pthread_t tid;

pthread_t clientthreads[100];

int readercount = 0;

FILE * fx;


// STRUCTURE TO STORE CONTACT
struct contact {

   long ph;

   char name[20], add[20], email[30], fun_name[20];

}
list, ll1, sort;

FILE * fp, * ft;

int i, n, ch, l, found;




// SEND THE CONTACT TO REQUESTER
void
send_file_display(int sockfd) {

   fx = fopen("data.log", "a");

   fprintf(fx, " in send_file_display \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   fp = fopen("contact.dll", "r");

   if (fp == NULL)

   {

      printf("file failed to open.");

      fx = fopen("data.log", "a");

      fprintf(fx, " fp failed in send_file_display \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   while (fread( & list, sizeof(list), 1, fp) == 1)

   {

      if (send(sockfd, & list, sizeof(list), 0) == -1)

      {

         printf("file not send sucessfully");

      }

   }

   strcpy(ll1.name, "exit");

   send(sockfd, & ll1, sizeof(ll1), 0);

   fclose(fp);

   fx = fopen("data.log", "a");

   fprintf(fx, "out display  \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   return;

}


//SEARCH THE FILE AND SEND TO CLIENT
void
send_file_searched(int sockfd, long search_ph) {

   fx = fopen("data.log", "a");

   fprintf(fx, "in send_file_searched   \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   fp = fopen("contact.dll", "r");

   if (fp == NULL)

   {

      printf("file failed to open.");

      fx = fopen("data.log", "a");

      fprintf(fx, "  fp failed in send_file_searched \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   struct contact sort;

   strcpy(sort.fun_name, "notfound");

   while (fread( & list, sizeof(list), 1, fp) == 1)

   {

      if (list.ph == search_ph)

      {

         send(sockfd, & list, sizeof(list), 0);

         strcpy(sort.fun_name, "found");

         break;

      }

   }

   strcpy(ll1.name, "exit");

   send(sockfd, & ll1, sizeof(ll1), 0);

   fclose(fp);

   send(sockfd, & sort, sizeof(sort), 0);

   fx = fopen("data.log", "a");

   fprintf(fx, "out send_file_searched   \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

}


//EDIT CONTACT AND INFORM BACK TO CLIENT
void
send_file_edit(int sockfd) {

   fx = fopen("data.log", "a");

   fprintf(fx, " in send_file_edit  \n");

   fclose(fx);

   // Lock the semaphore
   sem_wait( & x);

   bool chk = false;

   struct contact sort;

   fp = fopen("contact.dll", "r");

   if (fp == NULL)

   {

      printf("file failed to open.");

      fx = fopen("data.log", "a");

      fprintf(fx, " fp failed in send_file_edit  \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   ft = fopen("temp.dat", "w");

   if (ft == NULL)

   {

      printf("file failed to open.");

      fx = fopen("data.log", "a");

      fprintf(fx, "  fp failed in send_file_edit \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   strcpy(sort.fun_name, "notfound");

   while (fread( & list, sizeof(list), 1, fp) == 1)

   {

      if (ll1.ph != list.ph)

      {

         fwrite( & list, sizeof(list), 1, ft);

      } else

      {

         chk = true;

      }

   }

   if (chk == true)

   {

      fwrite( & ll1, sizeof(ll1), 1, ft);

      strcpy(sort.fun_name, "Edited");

   } else

   {

      strcpy(sort.fun_name, "not_edited");

   }

   fclose(fp);

   fclose(ft);

   remove("contact.dll");

   rename("temp.dat", "contact.dll");

   send(sockfd, & sort, sizeof(sort), 0);

   // Unlock the semaphore
   sem_post( & x);

   fx = fopen("data.log", "a");

   fprintf(fx, " out send_file_edit  \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   return;

}


//DELETE CONTACT AND INFROM BACK TO CLIENT
void
send_file_delete(int sockfd) {

   fx = fopen("data.log", "a");

   fprintf(fx, "in send_file_delete   \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   struct contact sort;

   fp = fopen("contact.dll", "r");

   if (fp == NULL)

   {

      printf("file failed to open.");

      fx = fopen("data.log", "a");

      fprintf(fx, " fp failed in send_file_delete  \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   ft = fopen("temp.dat", "w");

   if (ft == NULL)

   {

      printf("file failed to open.");

      fx = fopen("data.log", "a");

      fprintf(fx, " ft failed in send_file_delete  \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   strcpy(sort.fun_name, "notfound");

   while (fread( & list, sizeof(list), 1, fp) == 1)

   {

      if (ll1.ph != list.ph)

      {

         fwrite( & list, sizeof(list), 1, ft);

      } else

      {

         strcpy(sort.fun_name, "found");

      }

   }

   fclose(fp);

   fclose(ft);

   remove("contact.dll");

   rename("temp.dat", "contact.dll");

   send(sockfd, & sort, sizeof(list), 0);

   fx = fopen("data.log", "a");

   fprintf(fx, " out send_file_delete \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   return;

}

//ADD THAT CONTACT AFTER CHECKING ITS ALREADY THERE OR NOT THEN ADD
bool send_file_add(int sockfd, struct contact demo) {

   fx = fopen("data.log", "a");

   fprintf(fx, "in send_file_add   \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   fp = fopen("contact.dll", "r");

   if (fp == NULL)

   {

      printf("file failed to open.");

      fx = fopen("data.log", "a");

      fprintf(fx, "fp failed in send_file_add   \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   while (fread( & ll1, sizeof(ll1), 1, fp) == 1)

   {

      if (ll1.ph == demo.ph)

      {

         fclose(fp);

         return true;

      }

   }

   fclose(fp);

   fx = fopen("data.log", "a");

   fprintf(fx, "out send_file_add \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   return false;

}

// Function designed for chat between client and server.
void *
   func(void * args) {

      int sockfd = * ((int * ) args);

      fx = fopen("data.log", "a");

      fprintf(fx, " in func\n ");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

      for (;;)

      {

         fx = fopen("data.log", "a");

         fprintf(fx, " in func in for start\n ");

         if (fx == NULL)

         {

            printf("fx has not opened");

         }

         fclose(fx);

         recv(sockfd, & list, sizeof(list), 0);

         if (strcmp(list.fun_name, "add") == 0)

         {

            fx = fopen("data.log", "a");

            fprintf(fx, " in add\n ");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

            if (send_file_add(sockfd, list) == 0)

            {

               struct contact sort1;

               fp = fopen("contact.dll", "a");

               if (fp == NULL)

               {

                  printf("file failed to open.");

                  fx = fopen("data.log", "a");

                  fprintf(fx, " fp has error in add  \n");

                  if (fx == NULL)

                  {

                     printf("fx has not opened");

                  }

                  fclose(fx);

               }

               fwrite( & list, sizeof(list), 1, fp);

               fclose(fp);

               strcpy(sort1.fun_name, "added");

               send(sockfd, & sort1, sizeof(sort1), 0);

               fx = fopen("data.log", "a");

               fprintf(fx, "   added contact\n");

               if (fx == NULL)

               {

                  printf("fx has not opened");

               }

               fclose(fx);

            } else

            {

               struct contact sort1;

               strcpy(sort1.fun_name, "notadded");

               send(sockfd, & sort1, sizeof(sort), 0);

               fx = fopen("data.log", "a");

               fprintf(fx, "not added contact   \n");

               if (fx == NULL)

               {

                  printf("fx has not opened");

               }

               fclose(fx);

            }

            fx = fopen("data.log", "a");

            fprintf(fx, "out add   \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

         }

         if (strcmp(list.fun_name, "display") == 0)

         {

            fx = fopen("data.log", "a");

            fprintf(fx, "  in display \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

            send_file_display(sockfd);

            fx = fopen("data.log", "a");

            fprintf(fx, "  out display \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

         }

         if (strcmp(list.fun_name, "search") == 0)

         {

            fx = fopen("data.log", "a");

            fprintf(fx, " in search  \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

            send_file_searched(sockfd, list.ph);

            fx = fopen("data.log", "a");

            fprintf(fx, "   out search\n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

         }

         if (strcmp(list.fun_name, "edit") == 0)

         {

            fx = fopen("data.log", "a");

            fprintf(fx, "  in edit \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

            ll1 = list;

            send_file_edit(sockfd);

            fx = fopen("data.log", "a");

            fprintf(fx, "   out edit\n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

         }

         if (strcmp(list.fun_name, "delete") == 0)

         {

            fx = fopen("data.log", "a");

            fprintf(fx, " in delete \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

            ll1 = list;

            send_file_delete(sockfd);

            fx = fopen("data.log", "a");

            fprintf(fx, " out delete  \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

         }

         if (strcmp(list.fun_name, "exit") == 0)

         {

            fx = fopen("data.log", "a");

            fprintf(fx, " exited thread  \n");

            if (fx == NULL)

            {

               printf("fx has not opened");

            }

            fclose(fx);

            pthread_exit(NULL);

            return 0;

         }

      }

      pthread_exit(NULL);

      return 0;

   }

// Driver Code
int
main() {

   fx = fopen("data.log", "a");

   fprintf(fx, "enter in main \n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   // Initialize variables
   int serverSocket, newSocket;

   struct sockaddr_in serverAddr;

   struct sockaddr_storage serverStorage;

   socklen_t addr_size;

   sem_init( & x, 0, 1);

   sem_init( & y, 0, 1);

   serverSocket = socket(AF_INET, SOCK_STREAM, 0);

   serverAddr.sin_addr.s_addr = INADDR_ANY;

   serverAddr.sin_family = AF_INET;

   serverAddr.sin_port = htons(8989);

   // Bind the socket to the
   // address and port number.
   bind(serverSocket,
      (struct sockaddr * ) & serverAddr,
      sizeof(serverAddr));

   // Listen on the socket,
   // with 40 max connection
   // requests queued
   if (listen(serverSocket, 50) == 0)

   {

      printf("Listening\n");

      fx = fopen("data.log", "a");

      fprintf(fx, "listining success\n");

      fclose(fx);

   } else

   {

      printf("Error\n");

      fx = fopen("data.log", "a");

      fprintf(fx, "error in connection not listning \n");

      if (fx == NULL)

      {

         printf("fx has not opened");

      }

      fclose(fx);

   }

   // Array for thread
   pthread_t tid[60];

   int i = 0;

   while (1)

   {

      addr_size = sizeof(serverStorage);

      // Extract the first
      // connection in the queue
      newSocket = accept(serverSocket,
         (struct sockaddr * ) & serverStorage, &
         addr_size);

      if (pthread_create( & clientthreads[i++], NULL,
            func, & newSocket)

         !=
         0)

      {

         // Error in creating thread
         printf("Failed to create thread\n");

         fx = fopen("data.log", "a");

         fprintf(fx, "error in creating tread\n");

         if (fx == NULL)

         {

            printf("fx has not opened");

         }

         fclose(fx);

      }

   }

   fx = fopen("data.log", "a");

   fprintf(fx, "exited sucess from main\n");

   if (fx == NULL)

   {

      printf("fx has not opened");

   }

   fclose(fx);

   return 0;

}
