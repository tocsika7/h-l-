#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

int main(){

	int player_atm;
	//table 
	int quit=0; 
	char oszlop_1[6];
    char oszlop_2[6];
    char oszlop_3[6];
    char oszlop_4[6];
    char oszlop_5[6];
    char oszlop_6[6];
    char oszlop_7[6];

	//Kliens kiéptés 
//--------------------------------------------------------------------------------------------
	int network_socket, ret;
	struct sockaddr_in server_address;
	char buffer_p1[1024];
	char buffer_p2[1024];

	int cleaner;

	network_socket = socket(AF_INET,SOCK_STREAM,0);

	memset(&server_address, '\0',sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int player_socket = accept(network_socket,NULL,NULL);

	ret = connect(network_socket,(struct sockaddr*)&server_address, sizeof(server_address));
	if(ret<0){
		printf("Csatlakozási hiba\n");
		exit(1);
	}
	printf("Csatlakozva a szerverre\n");

//-----------------------------------------------------------------------------------------------	

	
		
for(;;){
	while((strcmp(buffer_p1,"feladom")!=0)&&(strcmp(buffer_p2,"feladom")!=0)){
		
		
		printf("Add meg az oszlopot! Írd feladom a játék feladásához \n");
		scanf("%s",&buffer_p1[0]);
		
		while((strcmp(buffer_p1,"1")!=0)&&(strcmp(buffer_p1,"2")!=0)&&(strcmp(buffer_p1,"3")!=0)&&(strcmp(buffer_p1,"4")!=0)&&(strcmp(buffer_p1,"5")!=0)&&(strcmp(buffer_p1,"6")!=0)&&(strcmp(buffer_p1,"7")!=0)&&(strcmp(buffer_p1,"feladom")!=0)){
			printf("Rossz oszlopszámot adtál meg! 1-7-ig add meg az oszlopszámot!\n");
			scanf("%s",&buffer_p1[0]);
			}
		if(strcmp(buffer_p1,"feladom")==0){
				close(network_socket);
				printf("Disconected from the server!\n");
				exit(1);
				}
		printf("Várakozás a másik játékosra\n");
		send(network_socket,buffer_p1,strlen(buffer_p1),0);



		
		

		


		if(recv(network_socket,buffer_p1,1024,0)<0){
		printf("Error in recieving data.\n");
		}
		else{
			printf("1. Oszlop: %s\n",buffer_p1);



		
		}
		}
	}



	


	return 0;
}


