#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#define MAXLEN 4096

bool client_started = false;
static int sockfd;

int socket(char *name){
  struct sockaddr_in server;
  struct hostent *hp;
  char buf[MAXLEN];
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if(sockfd < 0){
    fprintf(stderr, "socket Failed\n");
    close(sockfd);
    exit(1);
  } 
  
  server.sin_family = AF_INET;
  
  hp = gethostbyname(name);
  if(hp == 0){
    fprintf(stderr,"Get Host Failed\n");
    close(sockfd);
    exit(1);
  }
  
  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_port = htons(4142);
  
  if(connect(sockfd,(struct sockaddr *) &server, sizeof(server)) < 0){
    fprintf(stderr, "Connect Failed\n");
    close(sockfd);
    exit(1);
  }
  client_started = true;
  return 0;
}

void client_start(){
  char ServerDes[MAXLEN] = "localhost";
  //printf("Csiechat Starting...\n");
  if(socket(ServerDes) == 0){
    //printf("Csiechat Started! FD: %d\n",sockfd);
  }
}
void client_end(){
  printf("There Are Stopped Jobs, just kidding.\n");
}

int main(int argc, char **argv){
  if(argc == 1){
    if(client_started){
      client_end();
    }
    else{
      client_start();
    }
  }
  else if(strcmp(argv[1],"start") == 0){
    client_start();
  }
  else if(strcmp(argv[1],"end") == 0){
    client_end();
  }
  else if(strcmp(argv[1],"chat") == 0){
    client_start();
    char message[MAXLEN] = {0};
    if(argc < 3){
      printf("Usage: ccc(or cc chat) (message)\nExample: ccc poi\n");
      return 0;
    }
    strcpy(message,argv[2]);
    for(int i=3; i<argc; i++){
      strcat(message," ");
      strcat(message,argv[i]);
    }
    if((send(sockfd, message, sizeof(message), 0)) < 0){
      fprintf(stderr, "send failed: %d\n",errno);
      close(sockfd);
      exit(1);
    }
    //printf("Sent %s\n",message);
  }
  
  return 0;
}
