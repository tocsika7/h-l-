#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444


void nulling(char t[]){
	for(int i=0;i<6;i++){
		t[i]=' ';
	}
}

void print_table(char t1[],char t2[],char t3[],char t4[],char t5[],char t6[],char t7[]){
	printf("[%c][%c][%c][%c][%c][%c][%c]\n",t1[0],t2[0],t3[0],t4[0],t5[0],t6[0],t7[0]);
	printf("[%c][%c][%c][%c][%c][%c][%c]\n",t1[1],t2[1],t3[1],t4[1],t5[1],t6[1],t7[1]);
	printf("[%c][%c][%c][%c][%c][%c][%c]\n",t1[2],t2[2],t3[2],t4[2],t5[2],t6[2],t7[2]);
	printf("[%c][%c][%c][%c][%c][%c][%c]\n",t1[3],t2[3],t3[3],t4[3],t5[3],t6[3],t7[3]);
	printf("[%c][%c][%c][%c][%c][%c][%c]\n",t1[4],t2[4],t3[4],t4[4],t5[4],t6[4],t7[4]);
	printf("[%c][%c][%c][%c][%c][%c][%c]\n",t1[5],t2[5],t3[5],t4[5],t5[5],t6[5],t7[5]);
}

int main(){
	//table 
	int quit=0; 
	char oszlop_1[6];
    char oszlop_2[6];
    char oszlop_3[6];
    char oszlop_4[6];
    char oszlop_5[6];
    char oszlop_6[6];
    char oszlop_7[6];
    

    //Dekalrációk


//Szerver képítése
//-------------------------------------------------------------------------------------------------------


	int binding;
	int cleaner1,cleaner2; 							//buffer tisztításához

	int player1_socket;
	int player2_socket;

	//szerver socket létrehozása 

	int server_socket;
	server_socket = socket(AF_INET,SOCK_STREAM,0);
	char buffer_p1[1024];
	char buffer_p2[1024];


	//address

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind

	binding = bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	if(binding!=0){
		printf("A porthoz való csatlakozás sikertelen\n");
		exit(1);
	}
	else{
		printf("A szerver elindult.\n");
		printf("Várakozás a Játékosok csatlakozására...\n");
	}

	listen(server_socket, 4);


	//Tábla kinullázása
	nulling(oszlop_1),nulling(oszlop_2),nulling(oszlop_3),nulling(oszlop_4),nulling(oszlop_5),nulling(oszlop_6),nulling(oszlop_7);

	print_table(oszlop_1,oszlop_2,oszlop_3,oszlop_4,oszlop_5,oszlop_6,oszlop_7);

	//Játékosok kapcsolódás a szerverre

	player1_socket = accept(server_socket,NULL,NULL);
	player2_socket = accept(server_socket,NULL,NULL);

	printf("Játékosok csatlakozva.\n");

		
		
//---------------------------------------------------------------------------------------------------------------

			while(1){
				cleaner1 = recv(player1_socket,buffer_p1,1024,0);
				buffer_p1[cleaner1]='\0';

				cleaner2 = recv(player2_socket,buffer_p2,1024,0);
				buffer_p2[cleaner2]='\0';

				if(strcmp(buffer_p1,"feladom")==0){
					printf("Disconected from %s:%d\n",inet_ntoa(server_address.sin_addr),ntohs(server_address.sin_port));
					break;
				}
				else{
					printf("Az az első játékos átlal megadott oszlop: %s\n",buffer_p1);
					send(player1_socket,buffer_p1,strlen(buffer_p1),0);
					send(player1_socket,oszlop_1,sizeof(oszlop_1),0);



					send(player2_socket,buffer_p2,strlen(buffer_p2),0);
					printf("A második játékos átlal megadott oszlop: %s\n",buffer_p2);
					
				}

			}
			

	close(server_socket);




	return 0;
}