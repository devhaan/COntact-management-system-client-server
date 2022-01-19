// C program for the Client Side
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/socket.h>

// inet_addr
#include <arpa/inet.h>

#include <unistd.h>


//@@@@@@@@@@@@@ Macros @@@@@@@@@@@@@@//
#define MAX 80
#define PORT 8000
#define SA struct sockaddr

//  dataStructure to store data
struct contact {
   long ph;
   char name[20], add[20], email[30], fun_name[20];

}
list, ll1;

// Global declaration
FILE * fp, * ft;
FILE * fx;
int ch;
int n;
char dummy;

//@@@@@@@@@@@@@ User defined Procedures @@@@@@@@@@@@@//

// this function will catch the contacts from server
void write_file(int sockfd) {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in write_file\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   // local var for internal use
   int n;
   int count = 0;

   printf("\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n\nName\t\tPhone No\t    Address\t\tE-mail ad.\n=================================================================\n\n");

   // for catching the contacts thrown by server////
   while (1) {

      recv(sockfd, & list, sizeof(list), 0);

      // loop breaking condition to get out from infinite loop		
      if (strcmp(list.name, "exit") == 0) {
         return;
      }

      // showing catched contact
      printf("\nName\t: %s\nPhone\t: %ld\nAddress\t: %s\nEmail\t: %s\n", list.name,
         list.ph, list.add, list.email);
   }
   fx = fopen("datac.log", "a");
   fprintf(fx, "out write_file\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   return;
}

// add contacts to file_system in server
void exit_connection(int sockfd) {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in exit_connection\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   system("clear");
   printf("\n\n\t\tAre you sure you want to exit?");

   strcpy(ll1.fun_name, "exit");

   send(sockfd, & ll1, sizeof(ll1), 0);
   fx = fopen("datac.log", "a");
   fprintf(fx, "out\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);

   return;
}

// add the contacts to file in server
void add_contact(int sockfd) {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in add_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   again: system("clear");
   printf("To exit enter blank space in the name input\nName (Use identical):");

   scanf("%[^\n]", list.name);

   getchar();

   printf("Phone:");
   list.ph = 0;
   scanf("%ld", & list.ph);
   if (list.ph == 0 || list.ph < 0) {
      system("clear");
      printf("Enter Valid number not use only 0 or nagative number other wise do again");
      getchar();

      goto again;
   }

   getchar();

   printf("address:");
   scanf("%[^\n]", list.add);

   getchar();

   printf("email address:");

   scanf("%[^\n]", list.email);

   getchar();

   printf("\n");

   strcpy(list.fun_name, "add");

   send(sockfd, & list, sizeof(list), 0);

   recv(sockfd, & ll1, sizeof(ll1), 0);
   system("clear");
   printf("Entered number is %s in directory\n\n\n", ll1.fun_name);
   printf("press enter for main menu : ");

   getchar();
   fx = fopen("datac.log", "a");
   fprintf(fx, "out add_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);

   return;
}

// to display the contact
void display_contact(int sockfd) {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in display_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   system("clear");
   strcpy(list.fun_name, "display");

   send(sockfd, & list, sizeof(list), 0);

   write_file(sockfd);

   printf("press enter for main menu : ");

   getchar();
   fx = fopen("datac.log", "a");
   fprintf(fx, "out display_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   return;
}

// to search the contact
void search_contact(int sockfd) {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in search_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   search: system("clear");
   printf("\n\n\t..::CONTACT SEARCH\n\t===========================\n\t..::Phone number of contact to search: ");

   fflush(stdin);

   list.ph = 0;
   scanf("%ld", & list.ph);
   if (list.ph == 0 || list.ph < 0) {
      system("clear");
      printf("Enter Valid number not use only 0 or nagative number other wise do again");
      getchar();
      getchar();
      goto search;
   }

   getchar();

   strcpy(list.fun_name, "search");

   send(sockfd, & list, sizeof(list), 0);

   write_file(sockfd);

   recv(sockfd, & ll1, sizeof(ll1), 0);
   if (strcmp(ll1.fun_name, "notfound") == 0) {
      system("clear");
      printf("Entered number is %s in directory \n\n\n", ll1.fun_name);

   }
   printf("press enter for main menu : ");
   getchar();

   fx = fopen("datac.log", "a");
   fprintf(fx, "out search_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);

   return;
}

// to edit the contact
void edit_contact(int sockfd) {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in edit_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   edit: system("clear");
   printf("..::Edit contact\n===============================\n\n\t..::Enter the name of contact to edit:");

   scanf("%[^\n]", list.name);

   getchar();

   printf("Phone:");

   list.ph = 0;
   scanf("%ld", & list.ph);
   if (list.ph == 0 || list.ph < 0) {
      system("clear");
      printf("Enter Valid number not use only 0 or nagative number other wise do again");
      getchar();
      getchar();
      goto edit;
   }

   getchar();

   printf("address:");
   scanf("%[^\n]", list.add);

   getchar();

   printf("email address:");

   scanf("%[^\n]", list.email);

   getchar();

   printf("\n");

   strcpy(list.fun_name, "edit");

   send(sockfd, & list, sizeof(list), 0);

   recv(sockfd, & ll1, sizeof(ll1), 0);
   system("clear");
   printf("Entered number is %s in directory \n\n\n", ll1.fun_name);

   printf("press enter for main menu : ");

   getchar();

   fx = fopen("datac.log", "a");
   fprintf(fx, "out edit_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);

   return;
}

// to delete the contact
void delete_contact(int sockfd) {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in delete_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   dlt: system("clear");
   printf("\n\n\t..::DELETE A CONTACT\n\t==========================\n\t..::Enter the numbers of contact to delete:");

   list.ph = 0;
   scanf("%ld", & list.ph);
   if (list.ph == 0 || list.ph < 0) {
      system("clear");
      printf("Enter Valid number not use only 0 or nagative number other wise do again");
      getchar();
      getchar();
      goto dlt;
   }

   getchar();

   strcpy(list.fun_name, "delete");

   send(sockfd, & list, sizeof(list), 0);

   recv(sockfd, & ll1, sizeof(list), 0);
   system("clear");
   printf("Entered number is %s in directory\n\n\n", ll1.fun_name);
   printf("press enter for main menu : ");

   getchar();
   fx = fopen("datac.log", "a");
   fprintf(fx, "out delete_contact\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   return;
}

// main funtionality 
void func(int sockfd) {

   /* ************Main menu ***********************  */

   main: system("clear");

   printf("\n\t **** Welcome to Contact Management System ****");

   printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Add a new Contact\n\t\t[2] List all Contacts\n\t\t[3] Search for contact\n\t\t[4] Edit a Contact\n\t\t[5] Delete Contact\n\t\t[0] Exit\n\t\t=================\n\t\t");

   printf("Enter the choice:");

   scanf("%d", & ch);
   getchar();

   switch (ch) {

   case 0:

      exit_connection(sockfd);

      break;

      /* *********************Add new contacts************  */

   case 1:
      add_contact(sockfd);

      goto main;

      /* *********************display contacts************  */

   case 2:
      display_contact(sockfd);

      goto main;

   case 3:
      search_contact(sockfd);

      goto main;

      /* *********************Edit  contacts************  */
   case 4:
      edit_contact(sockfd);

      goto main;

      /* *********************Delete  contacts************  */
   case 5:

      delete_contact(sockfd);
      goto main;

   default:

      printf("Invalid choice");

      break;

   }

   return;
}

// Driver Code
int main() {
   fx = fopen("datac.log", "a");
   fprintf(fx, "in main\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   int network_socket;

   // Create a stream socket
   network_socket = socket(AF_INET,
      SOCK_STREAM, 0);

   // Initialise port number and address
   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = INADDR_ANY;
   server_address.sin_port = htons(8989);

   // Initiate a socket connection
   int connection_status = connect(network_socket,
      (struct sockaddr * ) & server_address,
      sizeof(server_address));

   // Check for connection error
   if (connection_status < 0) {
      puts("Error\n");
      fx = fopen("datac.log", "a");
      fprintf(fx, "error in connecting\n");
      if (fx == NULL) {
         printf("fx has not opened");
      }
      fclose(fx);
      return 0;
   }

   printf("Connection established\n");
   fx = fopen("datac.log", "a");
   fprintf(fx, "connection done\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);

   // Send data to the socket
   func(network_socket);

   // Close the connection
   close(network_socket);
   fx = fopen("datac.log", "a");
   fprintf(fx, "out main\n");
   if (fx == NULL) {
      printf("fx has not opened");
   }
   fclose(fx);
   return 0;
}
